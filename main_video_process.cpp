#include "include/main.h"

int main_video_process(int argc, char *argv[])
{
    if(argc < 4)
    {
        printf("./motion_estimation movie.yuv 1920 1080 [result.csv]\n");
        exit(1);
    }

    clock_t start=clock();

    int width=atoi(argv[2]);
    int height=atoi(argv[3]);
    int total=width*height;
    size_t frame_bytes=total+total/4+total/4;

    FILE *fp_in=fopen(argv[1], "rb");
    if(NULL==fp_in)
    {
        fprintf(stderr, "cant open %s\n", argv[1]);
        exit(1);
    }

    fseek(fp_in, 0, 2);
    long filesize = ftell(fp_in);
    fseek(fp_in, 0, 0);

    struct img_yuv_t *frame_prev=img_yuv_create(width, height, 0);
    struct img_yuv_t *frame=img_yuv_create(width, height, 0);
    struct img_yuv_t *tmp;

    unsigned char *frame_buf=(unsigned char *)malloc(sizeof(unsigned char)*frame_bytes);
    fread(frame_buf, 1, frame_bytes, fp_in);
    buf_to_img_yuv(frame_buf,frame_prev);

    int krnl1[][3]={{ 0, 1, 0},
                    { 1,-4, 1},
                    { 0, 1, 0}};
    int krnl2[][3]={{ 1, 1, 1},
                    { 1,-8, 1},
                    { 1, 1, 1}};
    int krnl3[][3]={{ 1,-2, 1},
                    {-2, 4,-2},
                    { 1,-2, 1}};

    FILE *fp_out;
    if(argc == 5) {
        fp_out=fopen(argv[4], "w");
        if(NULL==fp_out)
        {
            fprintf(stderr, "cant open %s\n", argv[4]);
            exit(1);
        }
    } else
        fp_out = stdout;

    fprintf(fp_out,",fullsearch,,kernel1,,kernel2,,kernel3,,matching\n");
    fprintf(fp_out,"frame#,ave_sad,matching,ave_sad,matching,ave_sad,matching,ave_sad,matching,ave_sad,matching\n");
    fflush(fp_out);

    int num_of_frame=0;
    while(frame_bytes==fread(frame_buf, 1, frame_bytes, fp_in))
    {
        buf_to_img_yuv(frame_buf,frame);

        // some process start
        struct img_t *img_curr=img_copy(width,height,frame->y);
        struct img_t *img_prev=img_copy(width,height,frame_prev->y);
        auto me_block_fullsearch         =me_block_create(img_curr, img_prev, 16, 16);
        auto me_block_fullsearch_edge1   =me_block_create(img_curr, img_prev, 16, 16);
        auto me_block_fullsearch_edge2   =me_block_create(img_curr, img_prev, 16, 16);
        auto me_block_fullsearch_edge3   =me_block_create(img_curr, img_prev, 16, 16);
        auto me_block_fullsearch_matching=me_block_create(img_curr, img_prev, 16, 16);

        fullsearch              (me_block_fullsearch,          pe_8bit_diff       );
        fullsearch_kernel(me_block_fullsearch_edge1,    pe_8bit_diff, krnl1);
        fullsearch_kernel(me_block_fullsearch_edge2,    pe_8bit_diff, krnl2);
        fullsearch_kernel(me_block_fullsearch_edge3,    pe_8bit_diff, krnl3);
        fullsearch_matching     (me_block_fullsearch_matching, pe_8bit_diff       );

        fprintf(fp_out,"%d,%f,%d,%f,%d,%f,%d,%f,%d,%f,%d\n", num_of_frame+2,
               me_block_calc_ave_cost_sad(me_block_fullsearch),          me_block_calc_sum_cost_match(me_block_fullsearch),
               me_block_calc_ave_cost_sad(me_block_fullsearch_edge1),    me_block_calc_sum_cost_match(me_block_fullsearch_edge1),
               me_block_calc_ave_cost_sad(me_block_fullsearch_edge2),    me_block_calc_sum_cost_match(me_block_fullsearch_edge2),
               me_block_calc_ave_cost_sad(me_block_fullsearch_edge3),    me_block_calc_sum_cost_match(me_block_fullsearch_edge3),
               me_block_calc_ave_cost_sad(me_block_fullsearch_matching), me_block_calc_sum_cost_match(me_block_fullsearch_matching));

        me_block_destruct(me_block_fullsearch         );
        me_block_destruct(me_block_fullsearch_edge1   );
        me_block_destruct(me_block_fullsearch_edge2   );
        me_block_destruct(me_block_fullsearch_edge3   );
        me_block_destruct(me_block_fullsearch_matching);

        img_destruct(img_prev);
        img_destruct(img_curr);
        num_of_frame++;
        // some process end

        img_yuv_to_buf(frame,frame_buf);

        fflush(fp_out);

        tmp=frame;
        frame=frame_prev;
        frame_prev=tmp;
    }

    printf("%.2f sec\n",  (double)(clock()-start)/CLOCKS_PER_SEC);

    fclose(fp_in);
    free(frame_buf);
    img_yuv_destruct(frame_prev);
    img_yuv_destruct(frame);

    return 0;
}


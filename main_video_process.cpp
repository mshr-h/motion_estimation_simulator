#include "include/main.h"

int main_video_process(int argc, char *argv[])
{
    if(argc < 7)
    {
        printf("./motion_estimation movie.yuv width height sw_range tb_size threshold [result.csv]\n");
        exit(1);
    }

    clock_t start=clock();

    int width       =atoi(argv[2]);
    int height      =atoi(argv[3]);
    int search_range=atoi(argv[4]);
    int tb_size     =atoi(argv[5]);
    int th          =atoi(argv[6]);

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

    uint8_t *frame_buf=(uint8_t *)malloc(sizeof(uint8_t)*frame_bytes);
    fread(frame_buf, 1, frame_bytes, fp_in);
    buf_to_img_yuv(frame_buf,frame_prev);

    FILE *fp_out;
    if(argc == 8) {
        fp_out=fopen(argv[7], "w");
        if(NULL==fp_out)
        {
            fprintf(stderr, "cant open %s\n", argv[7]);
            exit(1);
        }
    } else
        fp_out = stdout;

    fprintf(fp_out,"width,%d\n"       , width);
    fprintf(fp_out,"height,%d\n"      , height);
    fprintf(fp_out,"threshold,%d\n"   , th);
    fprintf(fp_out,"search range,%d\n", search_range);
    fprintf(fp_out,"TB size,%d\n"     , tb_size);
    fprintf(fp_out,",FS with 8bit,,FS with 4bit,,4pix 2bit AD 6bit XOR,,breakingoff with 8bit,,breakingoff with 4bit,,breakingoff with 2bit AD 6bit XOR,\n");
    fprintf(fp_out,"frame#,SAD,PSNR,SAD,PSNR,SAD,PSNR,SAD,PSNR,SAD,PSNR,SAD,PSNR\n");
    fflush(fp_out);

    int num_of_frame=0;
    while(frame_bytes==fread(frame_buf, 1, frame_bytes, fp_in))
    {
        buf_to_img_yuv(frame_buf,frame);

        // some process start
        auto img_curr=img_copy(width,height,frame->y);
        auto img_prev=img_copy(width,height,frame_prev->y);
        auto me_block_fullsearch_8bit                   = me_block_create(img_curr, img_prev, search_range, tb_size);
        auto me_block_fullsearch_4bit                   = me_block_create(img_curr, img_prev, search_range, tb_size);
        auto me_block_fullsearch_4pix_2bit_ad_6bit_exor = me_block_create(img_curr, img_prev, search_range, tb_size);
        auto me_block_breakingoff_8bit                  = me_block_create(img_curr, img_prev, search_range, tb_size);
        auto me_block_breakingoff_4bit                  = me_block_create(img_curr, img_prev, search_range, tb_size);
        auto me_block_breakingoff_2bit_ad_6bit_exor     = me_block_create(img_curr, img_prev, search_range, tb_size);

        fullsearch      (me_block_fullsearch_8bit                   , pe_8bit_diff           , compare_SAD);
        fullsearch      (me_block_fullsearch_4bit                   , pe_4bit_diff           , compare_SAD);
        fullsearch_4pix (me_block_fullsearch_4pix_2bit_ad_6bit_exor , pe_2bit_diff_6bit_exor , compare_SAD);
        breakingoff     (me_block_breakingoff_8bit                  , pe_8bit_diff           , compare_SAD, th);
        breakingoff     (me_block_breakingoff_4bit                  , pe_4bit_diff           , compare_SAD, th/16);
        breakingoff     (me_block_breakingoff_2bit_ad_6bit_exor     , pe_2bit_diff_6bit_exor , compare_SAD, th);

        fprintf(fp_out,"%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
                num_of_frame+2,
                me_block_calc_ave_cost_sad(me_block_fullsearch_8bit),
                me_block_calc_psnr        (me_block_fullsearch_8bit),
                me_block_calc_ave_cost_sad(me_block_fullsearch_4bit),
                me_block_calc_psnr        (me_block_fullsearch_4bit),
                me_block_calc_ave_cost_sad(me_block_fullsearch_4pix_2bit_ad_6bit_exor),
                me_block_calc_psnr        (me_block_fullsearch_4pix_2bit_ad_6bit_exor),
                me_block_calc_ave_cost_sad(me_block_breakingoff_8bit),
                me_block_calc_psnr        (me_block_breakingoff_8bit),
                me_block_calc_ave_cost_sad(me_block_breakingoff_4bit),
                me_block_calc_psnr        (me_block_breakingoff_4bit),
                me_block_calc_ave_cost_sad(me_block_breakingoff_2bit_ad_6bit_exor),
                me_block_calc_psnr        (me_block_breakingoff_2bit_ad_6bit_exor));

        me_block_destruct(me_block_fullsearch_8bit);
        me_block_destruct(me_block_fullsearch_4bit);
        me_block_destruct(me_block_fullsearch_4pix_2bit_ad_6bit_exor);
        me_block_destruct(me_block_breakingoff_8bit);
        me_block_destruct(me_block_breakingoff_4bit);
        me_block_destruct(me_block_breakingoff_2bit_ad_6bit_exor);

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


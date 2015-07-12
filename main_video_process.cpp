#include "include/main.h"

int main_video_process(int argc, char *argv[])
{
    if(argc < 4)
    {
        printf("./motion_estimation movie.yuv 1920 1080\n");
        exit(1);
    }

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

    double ave_pe_1bit_diff           = 0;
    double ave_pe_2bit_diff           = 0;
    double ave_pe_3bit_diff           = 0;
    double ave_pe_4bit_diff           = 0;
    double ave_pe_5bit_diff           = 0;
    double ave_pe_6bit_diff           = 0;
    double ave_pe_7bit_diff           = 0;
    double ave_pe_8bit_diff           = 0;
    double ave_pe_2bit_diff_6bit_exor = 0;
    double ave_pe_3bit_diff_5bit_exor = 0;
    double ave_pe_4bit_diff_4bit_exor = 0;
    double ave_pe_5bit_diff_3bit_exor = 0;
    double ave_pe_6bit_diff_2bit_exor = 0;

    int num_of_frame=0;
    while(frame_bytes==fread(frame_buf, 1, frame_bytes, fp_in))
    {
        buf_to_img_yuv(frame_buf,frame);

        // some process start
        struct img_t *img_curr=img_copy(width,height,frame->y);
        struct img_t *img_prev=img_copy(width,height,frame_prev->y);
        auto me_block=me_block_create(img_curr,img_prev,16,16);

        fullsearch(me_block,pe_1bit_diff);           ave_pe_1bit_diff          +=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_2bit_diff);           ave_pe_2bit_diff          +=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_3bit_diff);           ave_pe_3bit_diff          +=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_4bit_diff);           ave_pe_4bit_diff          +=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_5bit_diff);           ave_pe_5bit_diff          +=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_6bit_diff);           ave_pe_6bit_diff          +=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_7bit_diff);           ave_pe_7bit_diff          +=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_8bit_diff);           ave_pe_8bit_diff          +=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_2bit_diff_6bit_exor); ave_pe_2bit_diff_6bit_exor+=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_3bit_diff_5bit_exor); ave_pe_3bit_diff_5bit_exor+=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_4bit_diff_4bit_exor); ave_pe_4bit_diff_4bit_exor+=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_5bit_diff_3bit_exor); ave_pe_5bit_diff_3bit_exor+=me_block_calc_average_cost(me_block);
        fullsearch(me_block,pe_6bit_diff_2bit_exor); ave_pe_6bit_diff_2bit_exor+=me_block_calc_average_cost(me_block);

        me_block_destruct(me_block);
        img_destruct(img_prev);
        img_destruct(img_curr);
        num_of_frame++;
        // some process end

        img_yuv_to_buf(frame,frame_buf);

        fflush(stdout);

        tmp=frame;
        frame=frame_prev;
        frame_prev=tmp;
    }

    ave_pe_1bit_diff           /= num_of_frame;
    ave_pe_2bit_diff           /= num_of_frame;
    ave_pe_3bit_diff           /= num_of_frame;
    ave_pe_4bit_diff           /= num_of_frame;
    ave_pe_5bit_diff           /= num_of_frame;
    ave_pe_6bit_diff           /= num_of_frame;
    ave_pe_7bit_diff           /= num_of_frame;
    ave_pe_8bit_diff           /= num_of_frame;
    ave_pe_2bit_diff_6bit_exor /= num_of_frame;
    ave_pe_3bit_diff_5bit_exor /= num_of_frame;
    ave_pe_4bit_diff_4bit_exor /= num_of_frame;
    ave_pe_5bit_diff_3bit_exor /= num_of_frame;
    ave_pe_6bit_diff_2bit_exor /= num_of_frame;

    printf("%s\n", argv[1]);
    printf("ave_pe_1bit_diff\t%f\n"           , ave_pe_1bit_diff          );
    printf("ave_pe_2bit_diff\t%f\n"           , ave_pe_2bit_diff          );
    printf("ave_pe_3bit_diff\t%f\n"           , ave_pe_3bit_diff          );
    printf("ave_pe_4bit_diff\t%f\n"           , ave_pe_4bit_diff          );
    printf("ave_pe_5bit_diff\t%f\n"           , ave_pe_5bit_diff          );
    printf("ave_pe_6bit_diff\t%f\n"           , ave_pe_6bit_diff          );
    printf("ave_pe_7bit_diff\t%f\n"           , ave_pe_7bit_diff          );
    printf("ave_pe_8bit_diff\t%f\n"           , ave_pe_8bit_diff          );
    printf("ave_pe_2bit_diff_6bit_exor\t%f\n" , ave_pe_2bit_diff_6bit_exor);
    printf("ave_pe_3bit_diff_5bit_exor\t%f\n" , ave_pe_3bit_diff_5bit_exor);
    printf("ave_pe_4bit_diff_4bit_exor\t%f\n" , ave_pe_4bit_diff_4bit_exor);
    printf("ave_pe_5bit_diff_3bit_exor\t%f\n" , ave_pe_5bit_diff_3bit_exor);
    printf("ave_pe_6bit_diff_2bit_exor\t%f\n" , ave_pe_6bit_diff_2bit_exor);

    fclose(fp_in);
    free(frame_buf);
    img_yuv_destruct(frame_prev);
    img_yuv_destruct(frame);

    return 0;
}


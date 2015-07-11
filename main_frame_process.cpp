#include "include/main.h"

int main_frame_process(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("./motion_estimation current_frame.png reference_frame.png\n");
        exit(1);
    }

    QString curr_fn=argv[1];
    QString prev_fn=argv[2];

    QImage curr_qimg(curr_fn);
    QImage prev_qimg(prev_fn);

    auto curr_img_rgb=QImage_to_img_rgb(&curr_qimg);
    auto prev_img_rgb=QImage_to_img_rgb(&prev_qimg);

    auto curr_img_yuv=img_rgb_to_yuv(curr_img_rgb);
    auto prev_img_yuv=img_rgb_to_yuv(prev_img_rgb);
    img_rgb_destruct(curr_img_rgb);
    img_rgb_destruct(prev_img_rgb);

    auto curr_img=img_copy(curr_img_yuv->wt,curr_img_yuv->ht,curr_img_yuv->y);
    auto prev_img=img_copy(prev_img_yuv->wt,prev_img_yuv->ht,prev_img_yuv->y);
    img_yuv_destruct(curr_img_yuv);
    img_yuv_destruct(prev_img_yuv);

    auto me_block=me_block_create(curr_img, prev_img, 16, 16);
    img_destruct(curr_img);
    img_destruct(prev_img);

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

    printf("\t%s\n", argv[1]); fflush(stdout);
    fullsearch(me_block,pe_1bit_diff); ave_pe_1bit_diff=me_block_calc_average_cost(me_block);
    printf("ave_pe_1bit_diff\t%f\n"           , ave_pe_1bit_diff          ); fflush(stdout);
    fullsearch(me_block,pe_2bit_diff); ave_pe_2bit_diff=me_block_calc_average_cost(me_block);
    printf("ave_pe_2bit_diff\t%f\n"           , ave_pe_2bit_diff          ); fflush(stdout);
    fullsearch(me_block,pe_3bit_diff); ave_pe_3bit_diff=me_block_calc_average_cost(me_block);
    printf("ave_pe_3bit_diff\t%f\n"           , ave_pe_3bit_diff          ); fflush(stdout);
    fullsearch(me_block,pe_4bit_diff); ave_pe_4bit_diff=me_block_calc_average_cost(me_block);
    printf("ave_pe_4bit_diff\t%f\n"           , ave_pe_4bit_diff          ); fflush(stdout);
    fullsearch(me_block,pe_5bit_diff); ave_pe_5bit_diff=me_block_calc_average_cost(me_block);
    printf("ave_pe_5bit_diff\t%f\n"           , ave_pe_5bit_diff          ); fflush(stdout);
    fullsearch(me_block,pe_6bit_diff); ave_pe_6bit_diff=me_block_calc_average_cost(me_block);
    printf("ave_pe_6bit_diff\t%f\n"           , ave_pe_6bit_diff          ); fflush(stdout);
    fullsearch(me_block,pe_7bit_diff); ave_pe_7bit_diff=me_block_calc_average_cost(me_block);
    printf("ave_pe_7bit_diff\t%f\n"           , ave_pe_7bit_diff          ); fflush(stdout);
    fullsearch(me_block,pe_8bit_diff); ave_pe_8bit_diff=me_block_calc_average_cost(me_block);
    printf("ave_pe_8bit_diff\t%f\n"           , ave_pe_8bit_diff          ); fflush(stdout);
    fullsearch(me_block,pe_2bit_diff_6bit_exor); ave_pe_2bit_diff_6bit_exor=me_block_calc_average_cost(me_block);
    printf("ave_pe_2bit_diff_6bit_exor\t%f\n" , ave_pe_2bit_diff_6bit_exor); fflush(stdout);
    fullsearch(me_block,pe_3bit_diff_5bit_exor); ave_pe_3bit_diff_5bit_exor=me_block_calc_average_cost(me_block);
    printf("ave_pe_3bit_diff_5bit_exor\t%f\n" , ave_pe_3bit_diff_5bit_exor); fflush(stdout);
    fullsearch(me_block,pe_4bit_diff_4bit_exor); ave_pe_4bit_diff_4bit_exor=me_block_calc_average_cost(me_block);
    printf("ave_pe_4bit_diff_4bit_exor\t%f\n" , ave_pe_4bit_diff_4bit_exor); fflush(stdout);
    fullsearch(me_block,pe_5bit_diff_3bit_exor); ave_pe_5bit_diff_3bit_exor=me_block_calc_average_cost(me_block);
    printf("ave_pe_5bit_diff_3bit_exor\t%f\n" , ave_pe_5bit_diff_3bit_exor); fflush(stdout);
    fullsearch(me_block,pe_6bit_diff_2bit_exor); ave_pe_6bit_diff_2bit_exor=me_block_calc_average_cost(me_block);
    printf("ave_pe_6bit_diff_2bit_exor\t%f\n" , ave_pe_6bit_diff_2bit_exor); fflush(stdout);

    me_block_destruct(me_block);

    return 0;
}


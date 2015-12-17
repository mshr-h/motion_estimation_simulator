
#include "include/main.h"

int main_frame_process(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("./motion_estimation current_frame.png reference_frame.png output.csv\n");
        exit(1);
    }

    clock_t start=clock();

    QImage prev_qimg(argv[1]);
    if(prev_qimg.isNull())
    {
        printf("couldn't open %s\n", argv[1]);
        exit(1);
    }

    QImage curr_qimg(argv[2]);
    if(curr_qimg.isNull())
    {
        printf("couldn't open %s\n", argv[2]);
        exit(1);
    }

    auto curr_img_rgb=QImage_to_img_rgb(&curr_qimg);
    auto prev_img_rgb=QImage_to_img_rgb(&prev_qimg);

    auto curr_img_yuv=img_rgb_to_yuv(curr_img_rgb);
    auto prev_img_yuv=img_rgb_to_yuv(prev_img_rgb);
    img_rgb_destruct(curr_img_rgb);
    img_rgb_destruct(prev_img_rgb);

    auto img_curr=img_copy(curr_img_yuv->wt,curr_img_yuv->ht,curr_img_yuv->y);
    auto img_prev=img_copy(prev_img_yuv->wt,prev_img_yuv->ht,prev_img_yuv->y);
    img_yuv_destruct(curr_img_yuv);
    img_yuv_destruct(prev_img_yuv);

    auto me_block_fullsearch=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_edge1=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_edge2=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_edge3=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_matching=me_block_create(img_curr, img_prev, 16, 16);
    img_destruct(img_curr);
    img_destruct(img_prev);

    // current method
    fullsearch(me_block_fullsearch, pe_8bit_diff);
    printf("curr : %d, sad: %f\n",
           me_block_calc_sum_cost_match(me_block_fullsearch),
           me_block_calc_average_cost(me_block_fullsearch));
    fflush(stdout);

    // proposed method 1
    int krnl1[][3] = {{0, 1,0},
                      {1,-4,1},
                      {0, 1,0}};
    fullsearch_filter_kernel(me_block_fullsearch_edge1, pe_8bit_diff, krnl1);
    printf("krnl1: %d, sad: %f\n",
           me_block_calc_sum_cost_match(me_block_fullsearch_edge1),
           me_block_calc_average_cost(me_block_fullsearch_edge1));
    fflush(stdout);

    // proposed method 2
    int krnl2[][3] = {{1, 1,1},
                      {1,-8,1},
                      {1, 1,1}};
    fullsearch_filter_kernel(me_block_fullsearch_edge2, pe_8bit_diff, krnl2);
    printf("krnl2: %d, sad: %f\n",
           me_block_calc_sum_cost_match(me_block_fullsearch_edge2),
           me_block_calc_average_cost(me_block_fullsearch_edge2));
    fflush(stdout);

    // proposed method 3
    int krnl3[][3] = {{ 1,-2, 1},
                      {-2, 4,-2},
                      { 1,-2, 1}};
    fullsearch_filter_kernel(me_block_fullsearch_edge3, pe_8bit_diff, krnl3);
    printf("krnl3: %d, sad: %f\n",
           me_block_calc_sum_cost_match(me_block_fullsearch_edge3),
           me_block_calc_average_cost(me_block_fullsearch_edge3));
    fflush(stdout);

    // proposed method 4
    fullsearch_matching(me_block_fullsearch_matching, pe_8bit_diff);
    printf("match: %d, sad: %f\n",
           me_block_calc_sum_cost_match(me_block_fullsearch_matching),
           me_block_calc_average_cost(me_block_fullsearch_matching));
    fflush(stdout);

    printf("%.2f sec\n",  (double)(clock()-start)/CLOCKS_PER_SEC);

    /*FILE *fp_out_csv=fopen(argv[3], "w");
    if(NULL==fp_out_csv)
    {
        fprintf(stderr, "%s:%d cannot open %s\n", __FILE__, __LINE__ , argv[3]);
        exit(1);
    }

    fclose(fp_out_csv);*/

    me_block_destruct(me_block_fullsearch);
    me_block_destruct(me_block_fullsearch_edge1);
    me_block_destruct(me_block_fullsearch_edge2);
    me_block_destruct(me_block_fullsearch_edge3);
    me_block_destruct(me_block_fullsearch_matching);

    return 0;
}

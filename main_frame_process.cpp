
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
    auto me_block_fullsearch_4pix=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_4pix_only=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_edge1=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_edge2=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_edge3=me_block_create(img_curr, img_prev, 16, 16);
    auto me_block_fullsearch_matching=me_block_create(img_curr, img_prev, 16, 16);
    img_destruct(img_curr);
    img_destruct(img_prev);

    // current method
    fullsearch(me_block_fullsearch, pe_8bit_diff);
    printf("curr : %6d, sad: %f\n",
           me_block_calc_sum_cost_match(me_block_fullsearch),
           me_block_calc_average_cost(me_block_fullsearch));
    fflush(stdout);

    // 4pix search method
    fullsearch_4pix(me_block_fullsearch_4pix, pe_8bit_diff);
    printf("4pix : %6d, sad: %f\n",
           me_block_calc_sum_cost_match(me_block_fullsearch_4pix),
           me_block_calc_average_cost(me_block_fullsearch_4pix));
    fflush(stdout);

    // 4pix only search method
    fullsearch_4pix_only(me_block_fullsearch_4pix_only, pe_8bit_diff);
    printf("4pixo: %6d, sad: %f\n",
           me_block_calc_sum_cost_match(me_block_fullsearch_4pix_only),
           me_block_calc_average_cost(me_block_fullsearch_4pix_only));
    fflush(stdout);

    // proposed method 4
    fullsearch_matching(me_block_fullsearch_matching, pe_8bit_diff);
    printf("match: %6d, sad: %f\n",
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
    me_block_destruct(me_block_fullsearch_4pix);
    me_block_destruct(me_block_fullsearch_edge1);
    me_block_destruct(me_block_fullsearch_edge2);
    me_block_destruct(me_block_fullsearch_edge3);
    me_block_destruct(me_block_fullsearch_matching);

    return 0;
}

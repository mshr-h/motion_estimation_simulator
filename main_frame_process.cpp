#include "include/main.h"

void printResult
(
        const char *method_name,
        const char *update_name,
        struct img_t *img_curr,
        struct img_t *img_prev,
        int sw_range,
        int tb_size,
        void (*search)(struct me_block_t *, unsigned char (*)(unsigned char, unsigned char), struct mvec_t (*)(struct mvec_t, struct mvec_t)),
        struct mvec_t (*update)(struct mvec_t, struct mvec_t)
)
{
    auto me_block=me_block_create(img_curr, img_prev, sw_range, tb_size);
    search(me_block, pe_8bit_diff, update);
    auto img_rec=me_block_reconstruct(me_block);
    printf("%s\t%s\t%d\t%f\t%f\n",
           method_name,
           update_name,
           me_block_calc_sum_cost_match(me_block),
           me_block_calc_ave_cost_sad(me_block),
           img_psnr(img_curr, img_rec));
    fflush(stdout);
    img_destruct(img_rec);
    me_block_destruct(me_block);
}

void printKrnlResult
(
        const char *method_name,
        const char *update_name,
        struct img_t *img_curr,
        struct img_t *img_prev,
        int sw_range,
        int tb_size,
        void (*search)(struct me_block_t *, unsigned char (*)(unsigned char, unsigned char), struct mvec_t (*)(struct mvec_t, struct mvec_t), int [3][3]),
        struct mvec_t (*update)(struct mvec_t, struct mvec_t),
        int krnl[3][3]
)
{
    auto me_block=me_block_create(img_curr, img_prev, sw_range, tb_size);
    search(me_block, pe_8bit_diff, update, krnl);
    auto img_rec=me_block_reconstruct(me_block);
    printf("%s\t%s\t%d\t%f\t%f\n",
           method_name,
           update_name,
           me_block_calc_sum_cost_match(me_block),
           me_block_calc_ave_cost_sad(me_block),
           img_psnr(img_curr, img_rec));
    fflush(stdout);
    img_destruct(img_rec);
    me_block_destruct(me_block);
}

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

    int krnl1[][3]={{ 0, 1, 0},
                    { 1,-4, 1},
                    { 0, 1, 0}};
    int krnl2[][3]={{ 1, 1, 1},
                    { 1,-8, 1},
                    { 1, 1, 1}};
    int krnl3[][3]={{ 1,-2, 1},
                    {-2, 4,-2},
                    { 1,-2, 1}};
    int sw_range=4;
    int tb_size=4;

    printf("SW\t%d\tTB\t%d\n", sw_range, tb_size);
    printf("method\tupdate\tmatch\tsad\tpsnr\n");
    printResult    ("fullsearch" , "SAD"         , img_curr, img_prev, sw_range, tb_size, fullsearch            , compare_SAD                );
    printResult    ("fullsearch" , "SAD+matching", img_curr, img_prev, sw_range, tb_size, fullsearch            , compare_SAD_matching       );
    printKrnlResult("fullsearch" , "SAD+kernel1" , img_curr, img_prev, sw_range, tb_size, fullsearch_kernel     , compare_SAD_minEdge , krnl1);
    printKrnlResult("fullsearch" , "SAD+kernel2" , img_curr, img_prev, sw_range, tb_size, fullsearch_kernel     , compare_SAD_minEdge , krnl2);
    printKrnlResult("fullsearch" , "SAD+kernel2" , img_curr, img_prev, sw_range, tb_size, fullsearch_kernel     , compare_SAD_minEdge , krnl3);
    printResult    ("4pix search", "SAD"         , img_curr, img_prev, sw_range, tb_size, fullsearch_4pix       , compare_SAD                );
    printResult    ("4pix search", "SAD+matching", img_curr, img_prev, sw_range, tb_size, fullsearch_4pix       , compare_SAD_matching       );
    printKrnlResult("4pix search", "SAD+kernel1" , img_curr, img_prev, sw_range, tb_size, fullsearch_4pix_kernel, compare_SAD_minEdge , krnl1);
    printKrnlResult("4pix search", "SAD+kernel2" , img_curr, img_prev, sw_range, tb_size, fullsearch_4pix_kernel, compare_SAD_minEdge , krnl2);
    printKrnlResult("4pix search", "SAD+kernel2" , img_curr, img_prev, sw_range, tb_size, fullsearch_4pix_kernel, compare_SAD_minEdge , krnl3);

    printf("%.2f sec\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    img_destruct(img_curr);
    img_destruct(img_prev);

    return 0;
}

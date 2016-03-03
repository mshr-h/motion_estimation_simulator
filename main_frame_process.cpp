#include "include/main.h"

void printResult
(
        const char *string,
        struct img_t *img_curr,
        struct img_t *img_prev,
        int sw_range,
        int tb_size,
        void (*search)(struct me_block_t *, uint8_t (*)(uint8_t, uint8_t), struct mvec_t (*)(struct mvec_t, struct mvec_t)),
        uint8_t (*pe)(uint8_t, uint8_t),
        struct mvec_t (*update)(struct mvec_t, struct mvec_t)
)
{
    auto me_block=me_block_create(img_curr, img_prev, sw_range, tb_size);
    search(me_block, pe, update);
    auto img_rec=me_block_reconstruct(me_block);
    printf("%s\t%d\t%f\t%f\n",
           string,
           me_block_calc_sum_cost_match(me_block),
           me_block_calc_ave_cost_sad(me_block),
           img_psnr(img_curr, img_rec));
    fflush(stdout);
    img_destruct(img_rec);
    me_block_destruct(me_block);
}

void printKrnlResult
(
        const char *string,
        struct img_t *img_curr,
        struct img_t *img_prev,
        int sw_range,
        int tb_size,
        void (*search)(struct me_block_t *, uint8_t (*)(uint8_t, uint8_t), struct mvec_t (*)(struct mvec_t, struct mvec_t), int [3][3]),
        uint8_t (*pe)(uint8_t, uint8_t),
        struct mvec_t (*update)(struct mvec_t, struct mvec_t),
        int krnl[3][3]
)
{
    auto me_block=me_block_create(img_curr, img_prev, sw_range, tb_size);
    search(me_block, pe, update, krnl);
    auto img_rec=me_block_reconstruct(me_block);
    printf("%s\t%d\t%f\t%f\n",
           string,
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

    QImage ref_qimg(argv[1]);
    if(ref_qimg.isNull())
    {
        printf("couldn't open %s\n", argv[1]);
        exit(1);
    }

    QImage cur_qimg(argv[2]);
    if(cur_qimg.isNull())
    {
        printf("couldn't open %s\n", argv[2]);
        exit(1);
    }

    auto cur_img_rgb=QImage_to_img_rgb(&cur_qimg);
    auto ref_img_rgb=QImage_to_img_rgb(&ref_qimg);

    auto cur_img_yuv=img_rgb_to_yuv(cur_img_rgb);
    auto ref_img_yuv=img_rgb_to_yuv(ref_img_rgb);
    img_rgb_destruct(cur_img_rgb);
    img_rgb_destruct(ref_img_rgb);

    auto img_curr=img_copy(cur_img_yuv->wt,cur_img_yuv->ht,cur_img_yuv->y);
    auto img_prev=img_copy(ref_img_yuv->wt,ref_img_yuv->ht,ref_img_yuv->y);
    img_yuv_destruct(cur_img_yuv);
    img_yuv_destruct(ref_img_yuv);

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
    printf("method\tpixel\tupdate\tmatch\tmin sad\tpsnr\n");
    printResult    ( "fullsearch\t8bit\tSAD"      , img_curr, img_prev, sw_range, tb_size, fullsearch            , pe_8bit_diff, compare_SAD                );
    printResult    ( "fullsearch\t8bit\tSAD+match", img_curr, img_prev, sw_range, tb_size, fullsearch            , pe_8bit_diff, compare_SAD_match          );
    printKrnlResult( "fullsearch\t8bit\tSAD+krnl1", img_curr, img_prev, sw_range, tb_size, fullsearch_kernel     , pe_8bit_diff, compare_SAD_minEdge , krnl1);
    printKrnlResult( "fullsearch\t8bit\tSAD+krnl2", img_curr, img_prev, sw_range, tb_size, fullsearch_kernel     , pe_8bit_diff, compare_SAD_minEdge , krnl2);
    printKrnlResult( "fullsearch\t8bit\tSAD+krnl2", img_curr, img_prev, sw_range, tb_size, fullsearch_kernel     , pe_8bit_diff, compare_SAD_minEdge , krnl3);
    printResult    ("4pix search\t8bit\tSAD"      , img_curr, img_prev, sw_range, tb_size, fullsearch_4pix       , pe_8bit_diff, compare_SAD                );
    printResult    ("4pix search\t8bit\tSAD+match", img_curr, img_prev, sw_range, tb_size, fullsearch_4pix       , pe_8bit_diff, compare_SAD_match          );
    printKrnlResult("4pix search\t8bit\tSAD+krnl1", img_curr, img_prev, sw_range, tb_size, fullsearch_4pix_kernel, pe_8bit_diff, compare_SAD_minEdge , krnl1);
    printKrnlResult("4pix search\t8bit\tSAD+krnl2", img_curr, img_prev, sw_range, tb_size, fullsearch_4pix_kernel, pe_8bit_diff, compare_SAD_minEdge , krnl2);
    printKrnlResult("4pix search\t8bit\tSAD+krnl2", img_curr, img_prev, sw_range, tb_size, fullsearch_4pix_kernel, pe_8bit_diff, compare_SAD_minEdge , krnl3);

    printf("%.2f sec\n", (double)(clock()-start)/CLOCKS_PER_SEC);

    img_destruct(img_curr);
    img_destruct(img_prev);

    return 0;
}

#include "include/main.h"

void printResult(struct img_t *img_curr, struct img_t *img_prev, void (*method)(struct me_block_t *, unsigned char (*)(unsigned char, unsigned char)), const char *name)
{
    auto me_block=me_block_create(img_curr, img_prev, 16, 16);
    method(me_block, pe_8bit_diff);
    auto img_rec=me_block_reconstruct(me_block);
    printf("%s: %6d, sad: %f, psnr: %f, ssim: %f\n",
           name,
           me_block_calc_sum_cost_match(me_block),
           me_block_calc_average_cost(me_block),
           img_psnr(img_curr, img_rec),
           img_ssim(img_curr, img_prev));
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

    printResult(img_curr, img_prev, fullsearch,           "full     ");
    printResult(img_curr, img_prev, fullsearch_4pix,      "full4pix ");
    printResult(img_curr, img_prev, fullsearch_4pix_only, "full4pixO");
    printResult(img_curr, img_prev, fullsearch_matching,  "fullmatch");

    img_destruct(img_curr);
    img_destruct(img_prev);

    return 0;
}

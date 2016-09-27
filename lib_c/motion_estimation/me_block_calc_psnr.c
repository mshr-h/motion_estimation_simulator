#include "include/motion_estimation.h"

double me_block_calc_psnr(struct me_block_t *me_block)
{
    struct img_t *rec_frame; // reconstructed frame
    rec_frame = me_block_reconstruct(me_block);

    double psnr = img_psnr(rec_frame, me_block->cur_frame);
    img_destruct(rec_frame);

    return psnr;
}

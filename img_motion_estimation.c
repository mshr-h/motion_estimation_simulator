#include "include/implab.h"
#include "include/motion_estimation.h"

void
img_motion_estimation(
        struct img_t *prev_image,
        struct img_t *curr_image,
        int size_tb,
        int range_sw
        )
{
    printf("%d\t", fullsearch     (prev_image, curr_image, size_tb, range_sw, pe_8bit));
    printf("%d\t", fullsearch_4pix(prev_image, curr_image, size_tb, range_sw, pe_4bit));
    printf("%d\t", fullsearch_4pix(prev_image, curr_image, size_tb, range_sw, pe_mix_diff1_xor7));
    printf("%d\t", fullsearch_4pix(prev_image, curr_image, size_tb, range_sw, pe_mix_diff2_xor6));
    printf("%d\t", fullsearch_4pix(prev_image, curr_image, size_tb, range_sw, pe_mix_diff3_xor5));
    printf("%d\t", fullsearch_4pix(prev_image, curr_image, size_tb, range_sw, pe_mix_diff4_xor4));
    printf("%d\t", fullsearch_4pix(prev_image, curr_image, size_tb, range_sw, pe_mix_diff5_xor3));
    printf("%d\t", fullsearch_4pix(prev_image, curr_image, size_tb, range_sw, pe_mix_diff6_xor2));
    printf("%d\n", fullsearch_4pix(prev_image, curr_image, size_tb, range_sw, pe_mix_diff7_xor1));

    fflush(stdout);
}

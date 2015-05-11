#include "include/implab.h"
#include "include/motion_estimation.h"

void
img_motion_estimation(
	struct img_t *prev_image,
	struct img_t *curr_image,
	int tb_size,
	int sw_range
)
{
	printf("%d\t", fullsearch     (prev_image, curr_image, tb_size, sw_range, pe_8bit));
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_4bit));
    printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_4bit_dynamic));
    printf("%d\n", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_mix_diff4_xor4));

	fflush(stdout);
}

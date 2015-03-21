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
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_4bit_proposed1));
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_1bit_xor));
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_2bit_xor));
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_3bit_xor));
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_4bit_xor));
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_5bit_xor));
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_6bit_xor));
	printf("%d\t", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_7bit_xor));
	printf("%d\n", fullsearch_4pix(prev_image, curr_image, tb_size, sw_range, pe_8bit_xor));

	fflush(stdout);
}

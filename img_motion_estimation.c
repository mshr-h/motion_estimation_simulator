#include "include/implab.h"
#include "include/motion_estimation.h"

void
img_motion_estimation(
	struct img_yuv_t *prev_image,
	struct img_yuv_t *curr_image,
	int tb_size,
	int sw_size
)
{
	int result_fullsearch_8bit = fullsearch_8bit(
				 prev_image,
				 curr_image,
				 tb_size,
				 sw_size);
	printf("Fullsearch 8bit             : %.1f%% (%d)\n",
		   (double)result_fullsearch_8bit*100/result_fullsearch_8bit,
		   result_fullsearch_8bit);

	int result_fullsearch_4bit_4pix = fullsearch_4bit_4pix(
				 prev_image,
				 curr_image,
				 tb_size,
				 sw_size);
	printf("Fullsearch 4bit 4pix        : %.1f%% (%d)\n",
		   (double)result_fullsearch_4bit_4pix*100/result_fullsearch_8bit,
		   result_fullsearch_4bit_4pix);

	int result_fullsearch_4bit_4pix_dynamic = fullsearch_4bit_4pix_dynamic(
				 prev_image,
				 curr_image,
				 tb_size,
				 sw_size);
	printf("Fullsearch 4bit 4pix dynamic: %.1f%% (%d)\n",
		   (double)result_fullsearch_4bit_4pix_dynamic*100/result_fullsearch_8bit,
		   result_fullsearch_4bit_4pix_dynamic);

	int result_fullsearch_4bit_4pix_proposed = fullsearch_4bit_4pix_proposed(
				 prev_image,
				 curr_image,
				 tb_size,
				 sw_size);
	printf("Fullsearch 4bit 4pix dynamic: %.1f%% (%d)\n",
		   (double)result_fullsearch_4bit_4pix_proposed*100/result_fullsearch_8bit,
		   result_fullsearch_4bit_4pix_proposed);

	fflush(stdout);
}

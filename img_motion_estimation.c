#include "include/implab.h"
#include "include/motion_estimation.h"

void
img_motion_estimation(
	struct img_rgb_t *prev_image,
	struct img_rgb_t *curr_image,
	int tb_size,
	int sw_size
)
{
	int average;        // average of SAD

	average = fullsearch_8bit(
				  prev_image,
				  curr_image,
				  tb_size,
				  sw_size);
	fprintf(stdout, "Full search                  : %d\n", average);
	fflush(stdout);

	average = fullsearch_4bit_4pix(
				  prev_image,
				  curr_image,
				  tb_size,
				  sw_size);
	fprintf(stdout, "Full search 4bit 4pix        : %d\n", average);
	fflush(stdout);

	average = fullsearch_4bit_4pix_dynamic(
				  prev_image,
				  curr_image,
				  tb_size,
				  sw_size);
	fprintf(stdout, "Full search 4bit 4pix dynamic: %d\n", average);
	fflush(stdout);
}

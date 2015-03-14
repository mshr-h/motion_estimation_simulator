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
	int result_fullsearch_8bit =
			fullsearch(prev_image,
					   curr_image,
					   tb_size,
					   sw_range,
					   pe_8bit);
	printf("Fullsearch 8bit                : %.1f%% (%d)\n",
		   result_fullsearch_8bit*100.0/result_fullsearch_8bit,
		   result_fullsearch_8bit);

	int result_fullsearch_8bit_xor =
			fullsearch(prev_image,
					   curr_image,
					   tb_size,
					   sw_range,
					   pe_8bit_xor);
	printf("Fullsearch 8bit xor            : %.1f%% (%d)\n",
		   result_fullsearch_8bit_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_8bit_xor);

	int result_fullsearch_4bit_4pix =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_4bit);
	printf("Fullsearch 4bit 4pix           : %.1f%% (%d)\n",
		   result_fullsearch_4bit_4pix*100.0/result_fullsearch_8bit,
		   result_fullsearch_4bit_4pix);

	int result_fullsearch_4bit_4pix_dynamic =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_4bit_dynamic);
	printf("Fullsearch 4bit 4pix dynamic   : %.1f%% (%d)\n",
		   result_fullsearch_4bit_4pix_dynamic*100.0/result_fullsearch_8bit,
		   result_fullsearch_4bit_4pix_dynamic);

	int result_fullsearch_4bit_4pix_proposed1 =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_4bit_proposed1);
	printf("Fullsearch 4bit 4pix proposed 1: %.1f%% (%d)\n",
		   result_fullsearch_4bit_4pix_proposed1*100.0/result_fullsearch_8bit,
		   result_fullsearch_4bit_4pix_proposed1);

	int result_fullsearch_4bit_4pix_proposed2 =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_4bit_proposed2);
	printf("Fullsearch 4bit 4pix proposed 2: %.1f%% (%d)\n",
		   result_fullsearch_4bit_4pix_proposed2*100.0/result_fullsearch_8bit,
		   result_fullsearch_4bit_4pix_proposed2);

	int result_fullsearch_1bit_4pix_xor =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_1bit_xor);
	printf("Fullsearch 1bit 4pix xor       : %.1f%% (%d)\n",
		   result_fullsearch_1bit_4pix_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_1bit_4pix_xor);

	int result_fullsearch_2bit_4pix_xor =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_2bit_xor);
	printf("Fullsearch 2bit 4pix xor       : %.1f%% (%d)\n",
		   result_fullsearch_2bit_4pix_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_2bit_4pix_xor);

	int result_fullsearch_3bit_4pix_xor =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_3bit_xor);
	printf("Fullsearch 3bit 4pix xor       : %.1f%% (%d)\n",
		   result_fullsearch_3bit_4pix_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_3bit_4pix_xor);

	int result_fullsearch_4bit_4pix_xor =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_4bit_xor);
	printf("Fullsearch 4bit 4pix xor       : %.1f%% (%d)\n",
		   result_fullsearch_4bit_4pix_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_4bit_4pix_xor);

	int result_fullsearch_5bit_4pix_xor =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_5bit_xor);
	printf("Fullsearch 5bit 4pix xor       : %.1f%% (%d)\n",
		   result_fullsearch_5bit_4pix_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_5bit_4pix_xor);

	int result_fullsearch_6bit_4pix_xor =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_6bit_xor);
	printf("Fullsearch 6bit 4pix xor       : %.1f%% (%d)\n",
		   result_fullsearch_6bit_4pix_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_6bit_4pix_xor);

	int result_fullsearch_7bit_4pix_xor =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_7bit_xor);
	printf("Fullsearch 7bit 4pix xor       : %.1f%% (%d)\n",
		   result_fullsearch_7bit_4pix_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_7bit_4pix_xor);

	int result_fullsearch_8bit_4pix_xor =
			fullsearch_4pix(prev_image,
							curr_image,
							tb_size,
							sw_range,
							pe_8bit_xor);
	printf("Fullsearch 8bit 4pix xor       : %.1f%% (%d)\n",
		   result_fullsearch_8bit_4pix_xor*100.0/result_fullsearch_8bit,
		   result_fullsearch_8bit_4pix_xor);

	fflush(stdout);
}

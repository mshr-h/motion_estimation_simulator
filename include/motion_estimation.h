#include "include/implab.h"
#define MAX_SAD (255*16*16)

int
fullsearch_8bit(
	struct img_yuv_t *prev_image,
	struct img_yuv_t *curr_image,
	int tb_size,
	int sw_size
);

int
fullsearch_4bit_4pix(
	struct img_yuv_t *prev_image,
	struct img_yuv_t *curr_image,
	int tb_size,
	int sw_size
);

int
fullsearch_4bit_4pix_dynamic(
	struct img_yuv_t *prev_image,
	struct img_yuv_t *curr_image,
	int tb_size,
	int sw_size
);

int
fullsearch_4bit_4pix_proposed(
	struct img_yuv_t *prev_image,
	struct img_yuv_t *curr_image,
	int tb_size,
	int sw_size
);

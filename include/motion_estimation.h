#include "include/implab.h"
#define MAX_SAD (255*16*16)

int
fullsearch_8bit(
	struct img_rgb_t *prev_image,
	struct img_rgb_t *curr_image,
	int tb_size,
	int sw_size
);

int
fullsearch_4bit_4pix(
	struct img_rgb_t *prev_image,
	struct img_rgb_t *curr_image,
	int tb_size,
	int sw_size
);

int
fullsearch_4bit_4pix_dynamic(
	struct img_rgb_t *prev_image,
	struct img_rgb_t *curr_image,
	int tb_size,
	int sw_size
);

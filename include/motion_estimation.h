#include "include/implab.h"
#include "include/processor_element.h"
#include "include/search_method.h"
#define MAX_SAD (255*16*16)

int
fullsearch_8bit(
	struct img_t *prev_image,
	struct img_t *curr_image,
	int size_tb,
	int range_sw
);

int
fullsearch_4bit_4pix(
	struct img_t *prev_image,
	struct img_t *curr_image,
	int size_tb,
	int range_sw
);

int
fullsearch_4bit_4pix_dynamic(
	struct img_t *prev_image,
	struct img_t *curr_image,
	int size_tb,
	int range_sw
);

int
fullsearch_4bit_4pix_proposed1(
	struct img_t *prev_image,
	struct img_t *curr_image,
	int size_tb,
	int range_sw
);

int
fullsearch_4bit_4pix_proposed2(
	struct img_t *prev_image,
	struct img_t *curr_image,
	int size_tb,
	int range_sw
);

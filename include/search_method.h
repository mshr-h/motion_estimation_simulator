int
fullsearch(
	struct img_t *prev_image,
	struct img_t *curr_image,
	int tb_size,
	int sw_range,
	int (*pe)(int pel_tb, int pel_sw)
);

int
fullsearch_4pix(
	struct img_t *prev_image,
	struct img_t *curr_image,
	int tb_size,
	int sw_range,
	int (*pe)(int pel_tb, int pel_sw)
);


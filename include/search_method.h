int
fullsearch(
        struct img_t *prev_image,
        struct img_t *curr_image,
        int size_tb,
        int range_sw,
        int (*pe)(int pel_tb, int pel_sw)
        );

int
fullsearch_4pix(
        struct img_t *prev_image,
        struct img_t *curr_image,
        int size_tb,
        int range_sw,
        int (*pe)(int pel_tb, int pel_sw)
        );


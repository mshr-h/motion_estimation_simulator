#ifndef IMPLAB_H
#define IMPLAB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structures
struct img_t{
	int wt;
	int ht;
	unsigned char **data;
};

struct img_rgb_t{
	int wt;
	int ht;
	unsigned char **r;
	unsigned char **g;
	unsigned char **b;
};
struct img_yuv_t{
	int wt;
	int ht;
	unsigned char **y;
	unsigned char **u;
	unsigned char **v;
};
struct pix_t{
	int w;
	int h;
};

// imp functions
#ifdef __cplusplus
extern "C" {
#endif
void
img_motion_estimation(
	struct img_t *curr_image,
	struct img_t *prev_image,
	int tb_size,
	int sw_range
);
struct img_t *
img_create(
	int wt,
	int ht,
	unsigned char init
);
void
img_destruct(
	struct img_t *img
);
struct img_t *
img_copy(
	int wt,
	int ht,
	unsigned char **data
);
struct img_rgb_t *
img_rgb_create(
	int wt,
	int ht,
	unsigned char init
);
void
img_rgb_destruct(
	struct img_rgb_t *img
);
struct img_yuv_t *
img_rgb_to_yuv(
	struct img_rgb_t *img_rgb
);
struct img_yuv_t *
img_yuv_create(
	int wt,
	int ht,
	unsigned char init
);
void
img_yuv_destruct(
	struct img_yuv_t *img
);
//
unsigned char  **
Malloc2D_uchr(
	int ht,
	int wt,
	unsigned char init
);
#ifdef __cplusplus
}
#endif
#endif // IMPLAB_H

#ifndef IMPLAB_H
#define IMPLAB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structures
struct img_rgb_t{
	int wt;
	int ht;
	unsigned char **r;
	unsigned char **g;
	unsigned char **b;
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
	struct img_rgb_t *curr_image,
	struct img_rgb_t *prev_image,
	int tb_size,
	int sw_size
);
struct img_rgb_t *
img_rgb_create(
	int wt,
	int ht,
	unsigned char init
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

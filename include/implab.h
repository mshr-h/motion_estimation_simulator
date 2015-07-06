#ifndef IMPLAB_H
#define IMPLAB_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX(x,y) ((x)>(y))?(x):(y)
#define MIN(x,y) ((x)<(y))?(x):(y)

// structures
struct img_t
{
    int wt;
    int ht;
    unsigned char **data;
};

struct img_rgb_t
{
    int wt;
    int ht;
    unsigned char **r;
    unsigned char **g;
    unsigned char **b;
};

struct img_yuv_t
{
    int wt;
    int ht;
    unsigned char **y;
    unsigned char **u;
    unsigned char **v;
};

// imp functions
#ifdef __cplusplus
extern "C" {
#endif
struct img_t *img_create(int wt, int ht, unsigned char init);
void img_destruct(struct img_t *img);
struct img_t *img_copy(int wt, int ht, unsigned char **data);
struct img_t *img_diff(struct img_t *img1, struct img_t *img2);
struct img_rgb_t *img_rgb_create(int wt, int ht, unsigned char init);
void img_rgb_destruct(struct img_rgb_t *img);
struct img_yuv_t *img_rgb_to_yuv(struct img_rgb_t *img_rgb);
struct img_yuv_t *img_yuv_create(int wt,int ht, unsigned char init);
void img_yuv_destruct(struct img_yuv_t *img);
unsigned char  **Malloc2D_uchr(int ht, int wt, unsigned char init);
#ifdef __cplusplus
}
#endif
#endif // IMPLAB_H

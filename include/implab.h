#ifndef IMPLAB_H
#define IMPLAB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define MAX(x,y) ((x)>(y))?(x):(y)
#define MIN(x,y) ((x)<(y))?(x):(y)

// structures
struct img_t
{
    int wt;
    int ht;
    uint8_t **data;
};

struct img_rgb_t
{
    int wt;
    int ht;
    uint8_t **r;
    uint8_t **g;
    uint8_t **b;
};

struct img_yuv_t
{
    int wt;
    int ht;
    uint8_t **y;
    uint8_t **u;
    uint8_t **v;
};

struct integrated_img_t
{
    int wt;
    int ht;
    int32_t **data;
};

// imp functions

#ifdef __cplusplus
extern "C" {
#endif
struct img_t *img_create(int wt, int ht, uint8_t init);
void img_destruct(struct img_t *img);
struct img_t *img_copy(int wt, int ht, uint8_t **data);
struct img_t *img_diff(struct img_t *img1, struct img_t *img2);
double img_psnr(struct img_t *img1, struct img_t *img2);
double img_ssim(struct img_t *img1, struct img_t *img2);
struct img_rgb_t *img_rgb_create(int wt, int ht, uint8_t init);
void img_rgb_destruct(struct img_rgb_t *img);
struct img_yuv_t *img_rgb_to_yuv(struct img_rgb_t *img_rgb);
struct img_yuv_t *img_yuv_create(int wt,int ht, uint8_t init);
void img_yuv_destruct(struct img_yuv_t *img);
void buf_to_img_yuv(uint8_t *frame_buf, struct img_yuv_t *frame);
void img_yuv_to_buf(struct img_yuv_t *frame, uint8_t *frame_buf);
struct img_rgb_t *img_yuv_to_rgb(struct img_yuv_t *img_yuv);
uint8_t  **Malloc2D_uchr(int ht, int wt, uint8_t init);
struct integrated_img_t *integrated_img_create(int wt, int ht, uint64_t init);
void integrated_img_destruct(struct integrated_img_t *img);
struct integrated_img_t *img_to_integrated(struct img_t *img);
int32_t  **Malloc2D_int32(int ht, int wt, int32_t init);
#ifdef __cplusplus
}
#endif
#endif // IMPLAB_H

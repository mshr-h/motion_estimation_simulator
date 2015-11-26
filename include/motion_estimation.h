#ifndef MOTION_ESTIMATION_H
#define MOTION_ESTIMATION_H
#include "include/implab.h"
#include <assert.h>

#define MAX_SAD (255*16*16)

// Structures
struct mvec_t
{
    int h;
    int w;
    int cost; // sum of absolute difference
    int cost_edge; // sum of absolute difference of edge image
    int cost_match; // number of matching pixels
};

struct mvec_table_t
{
    int ht;
    int wt;
    struct mvec_t **data;
};

struct me_block_t
{
    int tb_size;
    int sw_range; // -16..+16
    struct img_t *curr_frame;
    struct img_t *prev_frame;
    struct mvec_table_t *mvec_table;
};

// motion estimation functions
#ifdef __cplusplus
extern "C" {
#endif
struct mvec_table_t *mvec_table_craete(int ht, int wt);
void mvec_table_destruct(struct mvec_table_t *mv_table);
struct me_block_t *me_block_create(struct img_t *curr, struct img_t *prev, int sw_range, int tb_size);
void me_block_destruct(struct me_block_t *me_block);
struct img_t *me_block_reconstruct(struct me_block_t *me);
double me_block_calc_average_cost(struct me_block_t *me_block);
int me_block_calc_sum_cost_match(struct me_block_t *me_block);

void fullsearch(struct me_block_t *me, unsigned char (*pe)(unsigned char, unsigned char));
void fullsearch_4pix(struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char));
void fullsearch_filter_kernel(struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char), int krnl[3][3]);
void fullsearch_matching(struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char));

#ifdef __cplusplus
}
#endif

#endif // MOTION_ESTIMATION_H


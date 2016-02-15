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
    int cost_sad; // sum of absolute difference
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
double me_block_calc_ave_cost_sad(struct me_block_t *me_block);
int me_block_calc_sum_cost_match(struct me_block_t *me_block);

void fullsearch                   (struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char), struct mvec_t (*update)(struct mvec_t, struct mvec_t));
void fullsearch_kernel            (struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char), struct mvec_t (*update)(struct mvec_t, struct mvec_t), int krnl[3][3]);
void fullsearch_4pix              (struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char), struct mvec_t (*update)(struct mvec_t, struct mvec_t));
void fullsearch_4pix_kernel       (struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char), struct mvec_t (*update)(struct mvec_t, struct mvec_t), int krnl[3][3]);
void fullsearch_4pix_only         (struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char), struct mvec_t (*update)(struct mvec_t, struct mvec_t));
void fullsearch_4pix_only_kernel  (struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char), struct mvec_t (*update)(struct mvec_t, struct mvec_t), int krnl[3][3]);

struct mvec_t compare_SAD         (struct mvec_t min_mvec, struct mvec_t cand_mvec);
struct mvec_t compare_SAD_matching(struct mvec_t min_mvec, struct mvec_t cand_mvec);
struct mvec_t compare_SAD_minEdge (struct mvec_t min_mvec, struct mvec_t cand_mvec);
struct mvec_t compare_SAD_maxEdge (struct mvec_t min_mvec, struct mvec_t cand_mvec);

#ifdef __cplusplus
}
#endif

#endif // MOTION_ESTIMATION_H


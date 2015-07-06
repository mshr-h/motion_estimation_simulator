#include "include/motion_estimation.h"

struct me_block_t *me_block_create(struct img_t *curr, struct img_t *prev, int sw_range, int tb_size)
{
    int h,w;
    int mv_table_h,mv_table_w;
    struct me_block_t *me_block;

    me_block=(struct me_block_t *)malloc(sizeof(struct me_block_t));

    me_block->sw_range=sw_range;
    me_block->tb_size=tb_size;

    me_block->curr_frame=img_copy(curr->wt,curr->ht,curr->data);
    me_block->prev_frame=img_copy(prev->wt,prev->ht,prev->data);

    mv_table_h=0;
    for(h=sw_range; (h+tb_size+sw_range)<me_block->curr_frame->ht; h+=tb_size)
        mv_table_h++;

    mv_table_w=0;
    for(w=sw_range; (w+tb_size+sw_range)<me_block->curr_frame->wt; w+=tb_size)
        mv_table_w++;


    me_block->mvec_table=mvec_table_craete(mv_table_h, mv_table_w);


    return me_block;
}

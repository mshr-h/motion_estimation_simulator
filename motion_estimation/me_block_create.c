#include "include/motion_estimation.h"

struct me_block_t *me_block_create(struct img_t *curr, struct img_t *prev, int sw_range, int tb_size)
{
    struct me_block_t *new_me;

    new_me=(struct me_block_t *)malloc(sizeof(struct me_block_t));

    new_me->sw_range=sw_range;
    new_me->tb_size=tb_size;

    new_me->curr_frame=img_copy(curr->wt,curr->ht,curr->data);
    new_me->prev_frame=img_copy(prev->wt,prev->ht,prev->data);

    return new_me;
}

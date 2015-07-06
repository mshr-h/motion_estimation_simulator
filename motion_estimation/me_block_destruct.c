#include "include/motion_estimation.h"

void me_block_destruct(struct me_block_t *me)
{
    free(me->curr_frame);
    free(me->prev_frame);
    free(me->mvec_table);
    free(me);
}

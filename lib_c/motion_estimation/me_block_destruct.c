#include "include/motion_estimation.h"

void me_block_destruct(struct me_block_t *me)
{
    mvec_table_destruct(me->mvec_table);
    img_destruct(me->curr_frame);
    img_destruct(me->prev_frame);
    free(me);
}

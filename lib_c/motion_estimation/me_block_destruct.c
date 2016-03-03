#include "include/motion_estimation.h"

void me_block_destruct(struct me_block_t *me)
{
    mvec_table_destruct(me->mvec_table);
    img_destruct(me->cur_frame);
    img_destruct(me->ref_frame);
    free(me);
}

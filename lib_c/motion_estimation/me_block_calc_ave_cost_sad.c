#include "include/motion_estimation.h"

double me_block_calc_ave_cost_sad(struct me_block_t *me_block)
{
    int h,w,sum=0;
    for(h=0;h<me_block->mvec_table->ht;h++)
    {
        for(w=0;w<me_block->mvec_table->wt;w++)
        {
            sum+=me_block->mvec_table->data[h][w].cost_sad;
        }
    }
    return (double)sum/( me_block->mvec_table->ht * me_block->mvec_table->wt );
}

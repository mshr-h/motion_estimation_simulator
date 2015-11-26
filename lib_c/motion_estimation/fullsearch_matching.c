#include "include/motion_estimation.h"

void fullsearch_matching(struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char))
{
    int h,w,lh,lw; // loop variables
    unsigned char curr_pix; // pixel value of current frame
    unsigned char prev_pix; // pixel value of previous frame
    struct mvec_t cand_mvec; // candidate motion vector
    struct mvec_t min_mvec; // minimum motion vector
    struct img_t *sw_memory;
    struct img_t *tb_memory;

    int sw_range=me_block->sw_range;
    int tb_size =me_block->tb_size;

    sw_memory=img_create(tb_size+2*sw_range, tb_size+2*sw_range, 0);
    tb_memory=img_create(tb_size, tb_size, 0);

    for(h=0; h<me_block->mvec_table->ht; h++)
    {
        for(w=0; w<me_block->mvec_table->wt; w++)
        {
            // copy tb and sw
            for(lh=0; lh<tb_memory->ht; lh++)
                for(lw=0; lw<tb_memory->wt; lw++)
                    tb_memory->data[lh][lw]=me_block->curr_frame->data[sw_range+tb_size*h+lh][sw_range+tb_size*w+lw];

            for(lh=0; lh<sw_memory->ht; lh++)
                for(lw=0; lw<sw_memory->wt; lw++)
                    sw_memory->data[lh][lw]=me_block->prev_frame->data[tb_size*h+lh][tb_size*w+lw];

            // find the motion vector which has the lowest matching error
            min_mvec.cost=MAX_SAD;
            min_mvec.cost_match=0;
            min_mvec.cost_edge=-1;
            for(cand_mvec.h=-sw_range; cand_mvec.h<=sw_range; cand_mvec.h++)
            {
                for(cand_mvec.w=-sw_range; cand_mvec.w<=sw_range; cand_mvec.w++)
                {
                    cand_mvec.cost=0;
                    cand_mvec.cost_match=0;
                    cand_mvec.cost_edge=-1;
                    for(lh=0; lh<tb_size; lh++)
                    {
                        for(lw=0; lw<tb_size; lw++)
                        {
                            curr_pix=tb_memory->data[lh][lw];
                            prev_pix=sw_memory->data[cand_mvec.h+sw_range+lh][cand_mvec.w+sw_range+lw];
                            cand_mvec.cost+=pe(curr_pix, prev_pix);

                            if(curr_pix==prev_pix)
                                cand_mvec.cost_match+=1;
                        }
                    }

                    // update mvec
                    if(min_mvec.cost > cand_mvec.cost)
                        min_mvec = cand_mvec;
                    else if(min_mvec.cost == cand_mvec.cost)
                    {
                        if(min_mvec.cost_match < cand_mvec.cost_match)
                            min_mvec = cand_mvec;
                    }
                }
            }

            me_block->mvec_table->data[h][w]= min_mvec;
        }
    }

    img_destruct(sw_memory);
    img_destruct(tb_memory);
}

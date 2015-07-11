#include "include/motion_estimation.h"

void fullsearch(struct me_block_t *me_block, unsigned char (*pe)(unsigned char, unsigned char))
{
    int h,w,lh,lw; // loop variables
    unsigned char curr_pix; // pixel value of current frame
    unsigned char prev_pix; // pixel value of previous frame
    struct mvec_t cand_mvec; // candidate motion vector
    struct mvec_t min_mvec; // minimum motion vector

    int sw_range=me_block->sw_range;
    int tb_size=me_block->tb_size;

    for(h=0; h<me_block->mvec_table->ht; h++)
    {
        for(w=0; w<me_block->mvec_table->wt; w++)
        {
            min_mvec.h=-sw_range;
            min_mvec.w=-sw_range;
            min_mvec.cost=MAX_SAD;
            for(cand_mvec.h=-sw_range; cand_mvec.h<=sw_range; cand_mvec.h++)
            {
                for(cand_mvec.w=-sw_range; cand_mvec.w<=sw_range; cand_mvec.w++)
                {
                    cand_mvec.cost=0;
#ifndef QT_NO_DEBUG
                    assert(cand_mvec.h >= -sw_range);
                    assert(cand_mvec.h <= sw_range);
                    assert(cand_mvec.w >= -sw_range);
                    assert(cand_mvec.w <= sw_range);
#endif
                    for(lh=0; lh<tb_size; lh++)
                    {
                        for(lw=0; lw<tb_size; lw++)
                        {
#ifndef QT_NO_DEBUG
                            assert(sw_range+tb_size*h+lh >= 0);
                            assert(sw_range+tb_size*h+lh < me_block->curr_frame->ht);
                            assert(sw_range+tb_size*w+lw >= 0);
                            assert(sw_range+tb_size*w+lw < me_block->curr_frame->wt);
                            assert(sw_range+tb_size*h+cand_mvec.h+lh >= 0);
                            assert(sw_range+tb_size*h+cand_mvec.h+lh < me_block->prev_frame->ht);
                            assert(sw_range+tb_size*w+cand_mvec.w+lw >= 0);
                            assert(sw_range+tb_size*w+cand_mvec.w+lw < me_block->prev_frame->wt);
#endif
                            curr_pix=me_block->curr_frame->data[sw_range+tb_size*h+lh][sw_range+tb_size*w+lw];
                            prev_pix=me_block->prev_frame->data[sw_range+tb_size*h+cand_mvec.h+lh][sw_range+tb_size*w+cand_mvec.w+lw];
                            cand_mvec.cost+=pe(curr_pix,prev_pix);
                        }
                    }
                    if(min_mvec.cost>cand_mvec.cost)
                    {
                        min_mvec=cand_mvec;
                    }
                }
            }

#ifndef QT_NO_DEBUG
            assert(min_mvec.h >= -sw_range);
            assert(min_mvec.h <= sw_range);
            assert(min_mvec.w >= -sw_range);
            assert(min_mvec.w <= sw_range);
#endif

            // recompute motion vector cost
            min_mvec.cost=0;
            for(lh=0; lh<tb_size; lh++)
            {
                for(lw=0; lw<tb_size; lw++)
                {
#ifndef QT_NO_DEBUG
                    assert(sw_range+tb_size*h+lh >= 0);
                    assert(sw_range+tb_size*h+lh < me_block->curr_frame->ht);
                    assert(sw_range+tb_size*w+lw >= 0);
                    assert(sw_range+tb_size*w+lw < me_block->curr_frame->wt);
                    assert(sw_range+tb_size*h+min_mvec.h+lh >= 0);
                    assert(sw_range+tb_size*h+min_mvec.h+lh < me_block->prev_frame->ht);
                    assert(sw_range+tb_size*w+min_mvec.w+lw >= 0);
                    assert(sw_range+tb_size*w+min_mvec.w+lw < me_block->prev_frame->wt);
#endif
                    curr_pix=me_block->curr_frame->data[sw_range+tb_size*h+lh][sw_range+tb_size*w+lw];
                    prev_pix=me_block->prev_frame->data[sw_range+tb_size*h+min_mvec.h+lh][sw_range+tb_size*w+min_mvec.w+lw];
                    min_mvec.cost+=abs(curr_pix-prev_pix);
                }
            }

            me_block->mvec_table->data[h][w]= min_mvec;
        }
    }
}

#include "include/motion_estimation.h"

void fullsearch_4pix(struct me_block_t *me_block, uint8_t (*pe)(uint8_t, uint8_t), struct mvec_t (*update)(struct mvec_t, struct mvec_t))
{
    int h,w,lh,lw; // loop variables
    uint8_t cur_pix; // pixel value of current frame
    uint8_t ref_pix; // pixel value of previous frame
    struct mvec_t cand_mvec; // candidate motion vector
    struct mvec_t min_mvec; // minimum motion vector
    struct mvec_t min_mvec2p; // 2pix accuracy minimum motion vector
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
                    tb_memory->data[lh][lw]=me_block->cur_frame->data[sw_range+tb_size*h+lh][sw_range+tb_size*w+lw];

            for(lh=0; lh<sw_memory->ht; lh++)
                for(lw=0; lw<sw_memory->wt; lw++)
                    sw_memory->data[lh][lw]=me_block->ref_frame->data[tb_size*h+lh][tb_size*w+lw];

            // find the motion vector which has the lowest matching error
            min_mvec.cost_sad=MAX_SAD;
            min_mvec.cost_match=0;
            min_mvec.cost_edge=-1;
            for(cand_mvec.h=-sw_range; cand_mvec.h<=sw_range; cand_mvec.h+=2)
            {
                for(cand_mvec.w=-sw_range; cand_mvec.w<=sw_range; cand_mvec.w+=2)
                {
                    cand_mvec.cost_sad=0;
                    cand_mvec.cost_match=0;
                    cand_mvec.cost_edge=-1;
                    for(lh=0; lh<tb_size; lh++)
                    {
                        for(lw=0; lw<tb_size; lw++)
                        {
                            cur_pix=tb_memory->data[lh][lw];
                            ref_pix=sw_memory->data[cand_mvec.h+sw_range+lh][cand_mvec.w+sw_range+lw];
                            cand_mvec.cost_sad+=pe(cur_pix, ref_pix);

                            if(cur_pix==ref_pix)
                                cand_mvec.cost_match+=1;
                        }
                    }

                    // update the best mvec
                    min_mvec = update(min_mvec, cand_mvec);
                }
            }

            min_mvec2p=min_mvec;

            // normalize minimum mvec
            min_mvec2p.h=MAX(MIN(min_mvec2p.h,sw_range-1),1-sw_range);
            min_mvec2p.w=MAX(MIN(min_mvec2p.w,sw_range-1),1-sw_range);

            // search in integer accuracy mode
            min_mvec.cost_sad=MAX_SAD;
            min_mvec.cost_match=0;
            min_mvec.cost_edge=-1;
            for(cand_mvec.h=min_mvec2p.h-1; cand_mvec.h<=min_mvec2p.h+1; cand_mvec.h++)
            {
                for(cand_mvec.w=min_mvec2p.w-1; cand_mvec.w<=min_mvec2p.w+1; cand_mvec.w++)
                {
                    cand_mvec.cost_sad=0;
                    cand_mvec.cost_match=0;
                    cand_mvec.cost_edge=-1;
                    for(lh=0; lh<tb_size; lh++)
                    {
                        for(lw=0; lw<tb_size; lw++)
                        {
                            cur_pix=tb_memory->data[lh][lw];
                            ref_pix=sw_memory->data[cand_mvec.h+sw_range+lh][cand_mvec.w+sw_range+lw];
                            cand_mvec.cost_sad+=abs(cur_pix-ref_pix);

                            if(cur_pix==ref_pix)
                                cand_mvec.cost_match+=1;
                        }
                    }

                    // update the best mvec
                    min_mvec = compare_SAD(min_mvec, cand_mvec);
                }
            }

            me_block->mvec_table->data[h][w]= min_mvec;
        }
    }

    img_destruct(sw_memory);
    img_destruct(tb_memory);
}

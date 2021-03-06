#include "include/motion_estimation.h"

void fullsearch_4pix_only_kernel(struct me_block_t *me_block, uint8_t (*pe)(uint8_t, uint8_t), struct mvec_t (*update)(struct mvec_t, struct mvec_t), int krnl[3][3])
{
    int h,w,lh,lw; // loop variables
    uint8_t cur_pix; // pixel value of current frame
    uint8_t ref_pix; // pixel value of previous frame
    uint8_t cur_edge_pix; // pixel value of current edged frame
    uint8_t ref_edge_pix; // pixel value of previous edged frame
    struct mvec_t cand_mvec; // candidate motion vector
    struct mvec_t min_mvec; // minimum motion vector
    struct img_t *sw_memory;
    struct img_t *tb_memory;
    struct img_t *sw_edge_memory;
    struct img_t *tb_edge_memory;

    int sw_range=me_block->sw_range;
    int tb_size =me_block->tb_size;

    sw_memory=img_create(tb_size+2*sw_range, tb_size+2*sw_range, 0);
    tb_memory=img_create(tb_size, tb_size, 0);
    sw_edge_memory=img_create(tb_size+2*sw_range, tb_size+2*sw_range, 0);
    tb_edge_memory=img_create(tb_size, tb_size, 0);

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

            // compute edge images
            for(lh=1; lh<tb_memory->ht-1; lh++)
                for(lw=1; lw<tb_memory->wt-1; lw++)
                    tb_edge_memory->data[lh][lw]
                            =krnl[0][0]*tb_memory->data[lh-1][lw-1]+krnl[0][1]*tb_memory->data[lh-1][lw  ]+krnl[0][2]*tb_memory->data[lh-1][lw+1]
                            +krnl[1][0]*tb_memory->data[lh  ][lw-1]+krnl[1][1]*tb_memory->data[lh  ][lw  ]+krnl[1][2]*tb_memory->data[lh  ][lw+1]
                            +krnl[2][0]*tb_memory->data[lh+1][lw-1]+krnl[2][1]*tb_memory->data[lh+1][lw  ]+krnl[2][2]*tb_memory->data[lh+1][lw+1];

            for(lh=1; lh<sw_memory->ht-1; lh++)
                for(lw=1; lw<sw_memory->wt-1; lw++)
                    sw_edge_memory->data[lh][lw]
                            =krnl[0][0]*sw_memory->data[lh-1][lw-1]+krnl[0][1]*sw_memory->data[lh-1][lw  ]+krnl[0][2]*sw_memory->data[lh-1][lw+1]
                            +krnl[1][0]*sw_memory->data[lh  ][lw-1]+krnl[1][1]*sw_memory->data[lh  ][lw  ]+krnl[1][2]*sw_memory->data[lh  ][lw+1]
                            +krnl[2][0]*sw_memory->data[lh+1][lw-1]+krnl[2][1]*sw_memory->data[lh+1][lw  ]+krnl[2][2]*sw_memory->data[lh+1][lw+1];

            // find the motion vector which has the lowest matching error
            min_mvec.cost_sad=MAX_SAD;
            min_mvec.cost_match=0;
            min_mvec.cost_edge=MAX_SAD;
            for(cand_mvec.h=-sw_range; cand_mvec.h<=sw_range; cand_mvec.h+=2)
            {
                for(cand_mvec.w=-sw_range; cand_mvec.w<=sw_range; cand_mvec.w+=2)
                {
                    cand_mvec.cost_sad=0;
                    cand_mvec.cost_match=0;
                    cand_mvec.cost_edge=0;
                    for(lh=0; lh<tb_size; lh++)
                    {
                        for(lw=0; lw<tb_size; lw++)
                        {
                            cur_pix=tb_memory->data[lh][lw];
                            ref_pix=sw_memory->data[cand_mvec.h+sw_range+lh][cand_mvec.w+sw_range+lw];
                            cand_mvec.cost_sad+=pe(cur_pix, ref_pix);

                            cur_edge_pix=tb_edge_memory->data[lh][lw];
                            ref_edge_pix=sw_edge_memory->data[cand_mvec.h+sw_range+lh][cand_mvec.w+sw_range+lw];
                            cand_mvec.cost_edge+=abs(cur_edge_pix-ref_edge_pix);

                            if(cur_pix==ref_pix)
                                cand_mvec.cost_match+=1;
                        }
                    }

                    // update the best mvec
                    min_mvec = update(min_mvec, cand_mvec);
                }
            }

            me_block->mvec_table->data[h][w]= min_mvec;
        }
    }

    img_destruct(sw_memory);
    img_destruct(tb_memory);
    img_destruct(sw_edge_memory);
    img_destruct(tb_edge_memory);
}

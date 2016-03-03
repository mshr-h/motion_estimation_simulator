#include "include/motion_estimation.h"

struct img_t *me_block_reconstruct(struct me_block_t *me)
{
    struct img_t *img;
    int h,w,lh,lw;
    int sw_range=me->sw_range;
    int tb_size=me->tb_size;
    uint8_t ref_pixel;

    img=img_create(me->cur_frame->wt, me->cur_frame->ht, 0);

    for(h=0; h<me->mvec_table->ht; h++)
    {
        for(w=0; w<me->mvec_table->wt; w++)
        {
            for(lh=0; lh<me->tb_size; lh++)
            {
                for(lw=0; lw<me->tb_size; lw++)
                {
#ifndef QT_NO_DEBUG
                            assert(sw_range+tb_size*h+me->mvec_table->data[h][w].h+lh >= 0);
                            assert(sw_range+tb_size*h+me->mvec_table->data[h][w].h+lh < me->cur_frame->ht);
                            assert(sw_range+tb_size*w+me->mvec_table->data[h][w].h+lw >= 0);
                            assert(sw_range+tb_size*w+me->mvec_table->data[h][w].h+lw < me->cur_frame->wt);
                            assert(sw_range+tb_size*h+lh >= 0);
                            assert(sw_range+tb_size*h+lh < me->cur_frame->ht);
                            assert(sw_range+tb_size*w+lw >= 0);
                            assert(sw_range+tb_size*w+lw < me->cur_frame->wt);
#endif
                    ref_pixel=me->ref_frame->data[sw_range+tb_size*h+me->mvec_table->data[h][w].h+lh][sw_range+tb_size*w+me->mvec_table->data[h][w].h+lw];
                    img->data[sw_range+tb_size*h+lh][sw_range+tb_size*w+lw]=ref_pixel;
                }
            }
        }
    }

    return img;
}

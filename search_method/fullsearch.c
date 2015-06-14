#include "include/implab.h"
#include "include/motion_estimation.h"

int
fullsearch(
        struct img_t *prev_image,
        struct img_t *curr_image,
        int size_tb,
        int range_sw,
        int (*pe)(int , int)
        )
{
    struct pix_t min_p; // position of minimum SAD (-16 .. +16, -1 .. +1)
    struct pix_t mb_p;  // posiiton of processing MB(Macro Block)
    struct pix_t sw_p;  // position of SW(Search Window) (-16 .. +16, -1 .. +1)
    struct pix_t tmp_p; // for SAD calculation
    int sad;            // sum of absolute difference
    int min_sad;        // size of minimum SAD
    int blcks;          // number of Macro Blocks
    int pel_sw;         // pixel value
    int pel_tb;         // pixel value
    int sum_min_sad;
    int average;        // average of SAD

    sum_min_sad = 0;
    blcks = 0;
    for(mb_p.h=size_tb; mb_p.h<(prev_image->ht-size_tb); mb_p.h+=size_tb) {
        for(mb_p.w=size_tb; mb_p.w<(prev_image->wt-size_tb); mb_p.w+=size_tb) {
            /* Integer Motion Estimation start */
            min_sad = MAX_SAD;
            min_p.h = -size_tb;
            min_p.w = -size_tb;
            for(sw_p.w=-size_tb; sw_p.w<=size_tb; sw_p.w++) {
                for(sw_p.h=-size_tb; sw_p.h<=size_tb; sw_p.h++) {
                    if((mb_p.h+sw_p.h)>=1064)
                        continue;
                    sad = 0;
                    for(tmp_p.h=0; tmp_p.h<size_tb; tmp_p.h++) {
                        for(tmp_p.w=0; tmp_p.w<size_tb; tmp_p.w++) {
                            pel_sw = curr_image->data[mb_p.h+sw_p.h+tmp_p.h][mb_p.w+sw_p.w+tmp_p.w];
                            pel_tb = prev_image->data[mb_p.h+tmp_p.h][mb_p.w+tmp_p.w];
                            sad += pe(pel_tb, pel_sw);
                        }
                    }
                    if(sad < min_sad) {
                        min_sad = sad;
                        min_p = sw_p;
                    }
                }
            }
            /* Integer Motion Estimation end */

            sum_min_sad += min_sad;
            blcks++;
        }
    }
    average = (int)((double)sum_min_sad/blcks + 0.5);
    return average;
}


#include "include/implab.h"
#include "include/motion_estimation.h"

int
fullsearch_4bit_4pix(
	struct img_yuv_t *prev_image,
	struct img_yuv_t *curr_image,
	int tb_size,
	int sw_size
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
	unsigned char **pimg = prev_image->y; // previous frame
	unsigned char **cimg = curr_image->y; // current  frame

	sum_min_sad = 0;
	blcks = 0;
	for(mb_p.h=tb_size; mb_p.h<(curr_image->ht-tb_size); mb_p.h+=tb_size) {
		for(mb_p.w=tb_size; mb_p.w<(curr_image->wt-tb_size); mb_p.w+=tb_size) {
			/* Double Motion Estimation start */
			min_sad = MAX_SAD;
			for(sw_p.w=-tb_size; sw_p.w<=tb_size; sw_p.w+=2) {
				for(sw_p.h=-tb_size; sw_p.h<=tb_size; sw_p.h+=2) {
					if(mb_p.h+sw_p.h>=1064)
						continue;
					sad = 0;
					for(tmp_p.h=0; tmp_p.h<tb_size; tmp_p.h++) {
						for(tmp_p.w=0; tmp_p.w<tb_size; tmp_p.w++) {
							pel_sw = cimg[mb_p.h+sw_p.h+tmp_p.h][mb_p.w+sw_p.w+tmp_p.w];
							pel_tb = pimg[mb_p.h+tmp_p.h][mb_p.w+tmp_p.w];
							pel_sw = (pel_sw >> 4) & 0x0f;
							pel_tb = (pel_tb >> 4) & 0x0f;
							sad += abs(pel_sw - pel_tb);
						}
					}
					if(sad < min_sad) {
						min_sad = sad;
						min_p = sw_p;
					}
				}
			}
			/* Double Motion Estimation end */

			/* Vector Normalization start */
			if(min_p.h == -16)
				min_p.h = -15;
			if(min_p.w == -16)
				min_p.w = -15;
			if(min_p.h == 16)
				min_p.h = 15;
			if(min_p.w == 16)
				min_p.w = 15;
			/* Vector Normalization end */

			/* Integer Motion Estimation start */
			min_sad = MAX_SAD;
			for(sw_p.w=-1; sw_p.w<=1; sw_p.w++) {
				for(sw_p.h=-1; sw_p.h<=1; sw_p.h++) {
					sad = 0;
					for(tmp_p.h=0; tmp_p.h<tb_size; tmp_p.h++) {
						for(tmp_p.w=0; tmp_p.w<tb_size; tmp_p.w++) {
							pel_sw = cimg[mb_p.h+min_p.h+sw_p.h+tmp_p.h][mb_p.w+min_p.w+sw_p.w+tmp_p.w];
							pel_tb = pimg[mb_p.h+tmp_p.h][mb_p.w+tmp_p.w];
							sad += abs(pel_sw - pel_tb);
						}
					}
					if(sad < min_sad) {
						min_sad = sad;
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

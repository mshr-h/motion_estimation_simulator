#include "include/implab.h"

#define MAX_SAD (255*16*16)

void
img_motion_estimation(
	struct img_rgb_t *prev_image,
	struct img_rgb_t *curr_image,
	int tb_size,
	int sw_size
)
{
	struct pix_t min_p; // position of minimum SAD (-16 .. +16, -1 .. +1)
	struct pix_t mb_p;  // posiiton of processing MB(Macro Block)
	struct pix_t sw_p;  // position of SW(Search Window) (-16 .. +16, -1 .. +1)
	struct pix_t tmp_p; // for SAD calculation
	int sad;
	int min_sad;        // size of minimum SAD
	int blcks;          // number of Macro Blocks
	int upperbit;
	int pel_sw;         // pixel value
	int pel_tb;         // pixel value
	int shift;          // shift amount
	int sum_min_sad;
	int ave;            // average of SAD
	unsigned char **pimg = prev_image->r; // previous frame
	unsigned char **cimg = curr_image->r; // current  frame

	/* Full search start */
	sum_min_sad = 0;
	blcks = 0;
	for(mb_p.h=tb_size; mb_p.h<(curr_image->ht-tb_size); mb_p.h+=tb_size) {
		for(mb_p.w=tb_size; mb_p.w<(curr_image->wt-tb_size); mb_p.w+=tb_size) {
			/* Integer Motion Estimation start */
			min_sad = MAX_SAD;
			for(sw_p.w=-tb_size; sw_p.w<=tb_size; sw_p.w++) {
				for(sw_p.h=-tb_size; sw_p.h<=tb_size; sw_p.h++) {
					if((mb_p.h+sw_p.h)>=1064)
						continue;
					sad = 0;
					for(tmp_p.h=0; tmp_p.h<tb_size; tmp_p.h++) {
						for(tmp_p.w=0; tmp_p.w<tb_size; tmp_p.w++) {
							pel_sw = cimg[mb_p.h+sw_p.h+tmp_p.h][mb_p.w+sw_p.w+tmp_p.w];
							pel_tb = pimg[mb_p.h+tmp_p.h][mb_p.w+tmp_p.w];
							sad += abs(pel_sw - pel_tb);
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
	ave = (int)((double)sum_min_sad/blcks + 0.5);
	fprintf(stdout, "Full search     ave_min_sad: %d\n", ave);
	fflush(stdout);
	/* Full search end */

	/* Current method start */
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
	ave = (int)((double)sum_min_sad/blcks + 0.5);
	fprintf(stdout, "Current method  ave_min_sad: %d\n", ave);
	fflush(stdout);
	/* Current method end */

	/* Proposed method start */
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
							upperbit = ((pel_sw ^ pel_tb) >> 6) & 0x3;
							switch (upperbit) {
								case 0: shift = 2; break; //   match   match
								case 1: shift = 3; break; //   match unmatch
								case 2: shift = 4; break; // unmatch   match
								case 3: shift = 4; break; // unmatch unmatch
								default:
									fprintf(stdout, "error occured!\n");
									fflush(stdout);
									exit(1);
							}
							pel_sw = pel_sw >> shift;
							pel_tb = pel_tb >> shift;
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
	ave = (int)((double)sum_min_sad/blcks + 0.5);
	fprintf(stdout, "Proposed method ave_min_sad: %d\n", ave);
	fflush(stdout);
	/* Proposed method end */
}

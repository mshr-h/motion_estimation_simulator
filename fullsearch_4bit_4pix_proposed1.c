#include "include/implab.h"
#include "include/motion_estimation.h"

/*
 * 6bit operation
 *    8bit    7bit
 *   match   match {[8:5], 2'b00}     ; << 0
 *   match unmatch {[8:5], 2'b00}     ; << 1
 * unmatch   match {1'b0, [7:4], 1'b0}; << 2
 * unmatch unmatch {2'b00, [6:3]}     ; << 2
 */

static int
pe(
	int pel_tb,
	int pel_sw
)
{
	int shift;          // shift amount
	int upperbits = ((pel_sw ^ pel_tb) >> 6) & 0x3;
	switch (upperbits) {
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

	int diff = abs(pel_sw - pel_tb);

	return diff << (shift - 2);
}

int
fullsearch_4bit_4pix_proposed1(
	struct img_t *prev_image,
	struct img_t *curr_image,
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

	unsigned char **pimg = prev_image->data; // previous frame
	unsigned char **cimg = curr_image->data; // current  frame

	sum_min_sad = 0;
	blcks = 0;
	for(mb_p.h=tb_size; mb_p.h<(prev_image->ht-tb_size); mb_p.h+=tb_size) {
		for(mb_p.w=tb_size; mb_p.w<(prev_image->wt-tb_size); mb_p.w+=tb_size) {
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
							sad += pe(pel_tb, pel_sw);
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

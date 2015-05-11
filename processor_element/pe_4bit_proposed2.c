#include "include/implab.h"
#include "include/motion_estimation.h"
#include <assert.h>

/*
 * 5bit operation
 *	8bit	7bit
 *   match   match {[8:5], 1'b0}
 *   match unmatch {[8:5], 1'b0}
 * unmatch   match {1'b0, [7:4]}
 * unmatch unmatch {2'b00, [6:4]}
 */

int
pe_4bit_proposed2(
	int pel_tb,
	int pel_sw
)
{
	int shift;  // shift amount
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
	pel_sw = (pel_sw >> shift) & 0xf; // 00xxxx00, 0xxxx000, xxxx0000
	pel_tb = (pel_tb >> shift) & 0xf; // xxxx
	assert(pel_sw >= 0);
	assert(pel_sw <= 15);
	assert(pel_tb >= 0);
	assert(pel_tb <= 15);

	int diff = abs(pel_sw - pel_tb);
	diff = diff << (shift - 2); // 00xxxx, 0xxxx0, xxxx00
	diff = diff >> 1;           // 00xxx,  0xxxx,  xxxx0
	assert(diff >= 0);
	assert(diff <= 30);

	return diff;
}

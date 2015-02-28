#include "include/implab.h"
#include "include/motion_estimation.h"

/*
 * 4bit operation
 *    8bit    7bit
 *   match   match [8:5]
 *   match unmatch [8:5]
 * unmatch   match [7:4]
 * unmatch unmatch [6:3]
 */

int
pe_4bit_dynamic(
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

	return abs(pel_sw - pel_tb);
}

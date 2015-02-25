#include "include/implab.h"
#include "include/motion_estimation.h"

int
pe_8bit(
	int pel_tb,
	int pel_sw
)
{
	return abs(pel_sw - pel_tb);
}

int
pe_4bit(
	int pel_tb,
	int pel_sw
)
{
	pel_sw = (pel_sw >> 4) & 0x0f;
	pel_tb = (pel_tb >> 4) & 0x0f;

	return abs(pel_sw - pel_tb);
}

int
pe_dynamic_4bit(
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

/*
 * 6bit operation
 *    8bit    7bit
 *   match   match {[8:5], 2'b00}     ; << 0
 *   match unmatch {[8:5], 2'b00}     ; << 1
 * unmatch   match {1'b0, [7:4], 1'b0}; << 2
 * unmatch unmatch {2'b00, [6:3]}     ; << 2
 */

int
pe_4bit_proposed1(
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

/*
 * 5bit operation
 *    8bit    7bit
 *   match   match {[8:5], 2'b00}     ; << 0
 *   match unmatch {[8:5], 2'b00}     ; << 1
 * unmatch   match {1'b0, [7:4], 1'b0}; << 2
 * unmatch unmatch {2'b00, [6:3]}     ; << 2
 */

//
// SORRY, UNIMPLEMENTED!!!
//
int
pe_4bit_proposed2(
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

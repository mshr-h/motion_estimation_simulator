#include "include/implab.h"
#include "include/motion_estimation.h"
#include <assert.h>

int
pe_4bit_xor(
	int pel_tb,
	int pel_sw
)
{
	pel_sw = (pel_sw >> 4) & 0x0f;
	pel_tb = (pel_tb >> 4) & 0x0f;
	assert(pel_sw >= 0);
	assert(pel_sw <= 15);
	assert(pel_tb >= 0);
	assert(pel_tb <= 15);

	return (pel_sw ^ pel_tb);
}

int
pe_5bit_xor(
	int pel_tb,
	int pel_sw
)
{
	pel_sw = (pel_sw >> 3) & 0x1f;
	pel_tb = (pel_tb >> 3) & 0x1f;
	assert(pel_sw >= 0);
	assert(pel_sw <= 31);
	assert(pel_tb >= 0);
	assert(pel_tb <= 31);

	return (pel_sw ^ pel_tb);
}

int
pe_6bit_xor(
	int pel_tb,
	int pel_sw
)
{
	pel_sw = (pel_sw >> 2) & 0x3f;
	pel_tb = (pel_tb >> 2) & 0x3f;
	assert(pel_sw >= 0);
	assert(pel_sw <= 63);
	assert(pel_tb >= 0);
	assert(pel_tb <= 63);

	return (pel_sw ^ pel_tb);
}

int
pe_7bit_xor(
	int pel_tb,
	int pel_sw
)
{
	pel_sw = (pel_sw >> 1) & 0x7f;
	pel_tb = (pel_tb >> 1) & 0x7f;
	assert(pel_sw >= 0);
	assert(pel_sw <= 127);
	assert(pel_tb >= 0);
	assert(pel_tb <= 127);

	return (pel_sw ^ pel_tb);
}

int
pe_8bit_xor(
	int pel_tb,
	int pel_sw
)
{
	assert(pel_sw >= 0);
	assert(pel_sw <= 255);
	assert(pel_tb >= 0);
	assert(pel_tb <= 255);

	return (pel_sw ^ pel_tb);
}

#include "include/implab.h"
#include "include/motion_estimation.h"
#include <assert.h>

int
pe_8bit(
	int pel_tb,
	int pel_sw
)
{
	assert(pel_sw >= 0);
	assert(pel_sw <= 255);
	assert(pel_tb >= 0);
	assert(pel_tb <= 255);
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
	assert(pel_sw >= 0);
	assert(pel_sw <= 15);
	assert(pel_tb >= 0);
	assert(pel_tb <= 15);

	return abs(pel_sw - pel_tb);
}

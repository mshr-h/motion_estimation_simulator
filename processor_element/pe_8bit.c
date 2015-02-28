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

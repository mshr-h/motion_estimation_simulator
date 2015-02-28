#include "include/implab.h"
#include "include/motion_estimation.h"

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

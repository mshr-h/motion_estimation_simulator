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

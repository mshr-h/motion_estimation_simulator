#include "include/implab.h"
#include "include/motion_estimation.h"
#include <assert.h>

int
pe_mix_diff4_xor1(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 4) & 0x0f; // upperbit
	int pel_tb_u = (pel_tb >> 4) & 0x0f; // upperbit
	int pel_sw_l = (pel_sw >> 1) & 0x01; // lowerbit
	int pel_tb_l = (pel_tb >> 3) & 0x01; // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 15);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 15);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 1);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 1);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 15);
	assert(pel_l >= 0);
	assert(pel_l <= 1);

	int pel = (pel_u << 1) | pel_l;
	assert(pel >= 0);
	assert(pel <= 31);

	return pel;
}

int
pe_mix_diff4_xor2(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 4) & 0x0f; // upperbit
	int pel_tb_u = (pel_tb >> 4) & 0x0f; // upperbit
	int pel_sw_l = (pel_sw >> 2) & 0x03; // lowerbit
	int pel_tb_l = (pel_tb >> 2) & 0x03; // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 15);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 15);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 3);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 3);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 15);
	assert(pel_l >= 0);
	assert(pel_l <= 3);

	int pel = (pel_u << 2) | pel_l;
	assert(pel >= 0);
	assert(pel <= 63);

	return pel;
}

int
pe_mix_diff4_xor3(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 4) & 0x0f; // upperbit
	int pel_tb_u = (pel_tb >> 4) & 0x0f; // upperbit
	int pel_sw_l = (pel_sw >> 1) & 0x07; // lowerbit
	int pel_tb_l = (pel_tb >> 1) & 0x07; // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 15);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 15);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 7);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 7);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 15);
	assert(pel_l >= 0);
	assert(pel_l <= 7);

	int pel = (pel_u << 3) | pel_l;
	assert(pel >= 0);
	assert(pel <= 127);

	return pel;
}

int
pe_mix_diff1_xor7(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 7) & 0x01; // upperbit
	int pel_tb_u = (pel_tb >> 7) & 0x01; // upperbit
	int pel_sw_l = pel_sw & 0x7f;        // lowerbit
	int pel_tb_l = pel_tb & 0x7f;        // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 1);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 1);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 127);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 127);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 1);
	assert(pel_l >= 0);
	assert(pel_l <= 127);

	int pel = (pel_u << 7) | pel_l;
	assert(pel >= 0);
	assert(pel <= 255);

	return pel;
}

int
pe_mix_diff2_xor6(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 6) & 0x03; // upperbit
	int pel_tb_u = (pel_tb >> 6) & 0x03; // upperbit
	int pel_sw_l = pel_sw & 0x3f;        // lowerbit
	int pel_tb_l = pel_tb & 0x3f;        // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 3);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 3);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 63);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 63);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 3);
	assert(pel_l >= 0);
	assert(pel_l <= 63);

	int pel = (pel_u << 6) | pel_l;
	assert(pel >= 0);
	assert(pel <= 255);

	return pel;
}

int
pe_mix_diff3_xor5(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 5) & 0x07; // upperbit
	int pel_tb_u = (pel_tb >> 5) & 0x07; // upperbit
	int pel_sw_l = pel_sw & 0x1f;        // lowerbit
	int pel_tb_l = pel_tb & 0x1f;        // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 7);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 7);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 31);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 31);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 7);
	assert(pel_l >= 0);
	assert(pel_l <= 31);

	int pel = (pel_u << 5) | pel_l;
	assert(pel >= 0);
	assert(pel <= 255);

	return pel;
}

int
pe_mix_diff4_xor4(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 4) & 0x0f; // upperbit
	int pel_tb_u = (pel_tb >> 4) & 0x0f; // upperbit
	int pel_sw_l = pel_sw & 0x0f;        // lowerbit
	int pel_tb_l = pel_tb & 0x0f;        // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 15);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 15);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 15);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 15);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 15);
	assert(pel_l >= 0);
	assert(pel_l <= 15);

	int pel = (pel_u << 4) | pel_l;
	assert(pel >= 0);
	assert(pel <= 255);

	return pel;
}

int
pe_mix_diff5_xor3(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 3) & 0x1f; // upperbit
	int pel_tb_u = (pel_tb >> 3) & 0x1f; // upperbit
	int pel_sw_l = pel_sw & 0x07;        // lowerbit
	int pel_tb_l = pel_tb & 0x07;        // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 31);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 31);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 7);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 7);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 31);
	assert(pel_l >= 0);
	assert(pel_l <= 7);

	int pel = (pel_u << 3) | pel_l;
	assert(pel >= 0);
	assert(pel <= 255);

	return pel;
}

int
pe_mix_diff6_xor2(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 2) & 0x3f; // upperbit
	int pel_tb_u = (pel_tb >> 2) & 0x3f; // upperbit
	int pel_sw_l = pel_sw & 0x03;        // lowerbit
	int pel_tb_l = pel_tb & 0x03;        // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 63);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 63);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 3);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 3);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 63);
	assert(pel_l >= 0);
	assert(pel_l <= 3);

	int pel = (pel_u << 2) | pel_l;
	assert(pel >= 0);
	assert(pel <= 255);

	return pel;
}

int
pe_mix_diff7_xor1(
	int pel_tb,
	int pel_sw
)
{
	int pel_sw_u = (pel_sw >> 1) & 0x7f; // upperbit
	int pel_tb_u = (pel_tb >> 1) & 0x7f; // upperbit
	int pel_sw_l = pel_sw & 0x01;        // lowerbit
	int pel_tb_l = pel_tb & 0x01;        // lowerbit
	assert(pel_sw_u >= 0);
	assert(pel_sw_u <= 127);
	assert(pel_tb_u >= 0);
	assert(pel_tb_u <= 127);
	assert(pel_sw_l >= 0);
	assert(pel_sw_l <= 1);
	assert(pel_tb_l >= 0);
	assert(pel_tb_l <= 1);

	int pel_u = abs(pel_sw_u - pel_tb_u);
	int pel_l = pel_sw_l ^ pel_tb_l;
	assert(pel_u >= 0);
	assert(pel_u <= 127);
	assert(pel_l >= 0);
	assert(pel_l <= 1);

	int pel = (pel_u << 1) | pel_l;
	assert(pel >= 0);
	assert(pel <= 255);

	return pel;
}

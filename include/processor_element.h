#ifndef PROCESSOR_ELEMENT_H
#define PROCESSOR_ELEMENT_H

#include "include/implab.h"
#include <assert.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif
uint8_t pe_1bit_diff(uint8_t a, uint8_t b);
uint8_t pe_2bit_diff(uint8_t a, uint8_t b);
uint8_t pe_3bit_diff(uint8_t a, uint8_t b);
uint8_t pe_4bit_diff(uint8_t a, uint8_t b);
uint8_t pe_5bit_diff(uint8_t a, uint8_t b);
uint8_t pe_6bit_diff(uint8_t a, uint8_t b);
uint8_t pe_7bit_diff(uint8_t a, uint8_t b);
uint8_t pe_8bit_diff(uint8_t a, uint8_t b);
uint8_t pe_2bit_diff_6bit_exor(uint8_t a, uint8_t b);
uint8_t pe_3bit_diff_5bit_exor(uint8_t a, uint8_t b);
uint8_t pe_4bit_diff_4bit_exor(uint8_t a, uint8_t b);
uint8_t pe_5bit_diff_3bit_exor(uint8_t a, uint8_t b);
uint8_t pe_6bit_diff_2bit_exor(uint8_t a, uint8_t b);
#ifdef __cplusplus
}
#endif

#endif // PROCESSOR_ELEMENT_H

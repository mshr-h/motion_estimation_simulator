#ifndef PROCESSOR_ELEMENT_H
#define PROCESSOR_ELEMENT_H
#include <assert.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif
unsigned char pe_1bit_diff(unsigned char a, unsigned char b);
unsigned char pe_2bit_diff(unsigned char a, unsigned char b);
unsigned char pe_3bit_diff(unsigned char a, unsigned char b);
unsigned char pe_4bit_diff(unsigned char a, unsigned char b);
unsigned char pe_5bit_diff(unsigned char a, unsigned char b);
unsigned char pe_6bit_diff(unsigned char a, unsigned char b);
unsigned char pe_7bit_diff(unsigned char a, unsigned char b);
unsigned char pe_8bit_diff(unsigned char a, unsigned char b);
unsigned char pe_2bit_diff_6bit_exor(unsigned char a, unsigned char b);
unsigned char pe_3bit_diff_5bit_exor(unsigned char a, unsigned char b);
unsigned char pe_4bit_diff_4bit_exor(unsigned char a, unsigned char b);
unsigned char pe_5bit_diff_3bit_exor(unsigned char a, unsigned char b);
unsigned char pe_6bit_diff_2bit_exor(unsigned char a, unsigned char b);
#ifdef __cplusplus
}
#endif

#endif // PROCESSOR_ELEMENT_H

#include"include/processor_element.h"

uint8_t pe_1bit_diff(uint8_t a, uint8_t b)
{
    int ret;
    ret=abs( ((a>>7)&0x1)-((b>>7)&0x1) );
#ifndef QT_NO_DEBUG
    assert(ret>=0);
    assert(ret<=0x1);
#endif
    return (uint8_t)ret;
}

uint8_t pe_2bit_diff(uint8_t a, uint8_t b)
{
    int ret;
    ret=abs( ((a>>6)&0x3)-((b>>6)&0x3) );
#ifndef QT_NO_DEBUG
    assert(ret>=0);
    assert(ret<=0x3);
#endif
    return (uint8_t)ret;
}

uint8_t pe_3bit_diff(uint8_t a, uint8_t b)
{
    int ret;
    ret=abs( ((a>>5)&0x7)-((b>>5)&0x7) );
#ifndef QT_NO_DEBUG
    assert(ret>=0);
    assert(ret<=0x7);
#endif
    return (uint8_t)ret;
}

uint8_t pe_4bit_diff(uint8_t a, uint8_t b)
{
    int ret;
    ret=abs( ((a>>4)&0xf)-((b>>4)&0xf) );
#ifndef QT_NO_DEBUG
    assert(ret>=0);
    assert(ret<=0xF);
#endif
    return (uint8_t)ret;
}

uint8_t pe_5bit_diff(uint8_t a, uint8_t b)
{
    int ret;
    ret=abs( ((a>>3)&0x1f)-((b>>3)&0x1f) );
#ifndef QT_NO_DEBUG
    assert(ret>=0);
    assert(ret<=0x1F);
#endif
    return (uint8_t)ret;
}

uint8_t pe_6bit_diff(uint8_t a, uint8_t b)
{
    int ret;
    ret=abs( ((a>>2)&0x3f)-((b>>2)&0x3f) );
#ifndef QT_NO_DEBUG
    assert(ret>=0);
    assert(ret<=0x3F);
#endif
    return (uint8_t)ret;
}

uint8_t pe_7bit_diff(uint8_t a, uint8_t b)
{
    int ret;
    ret=abs( ((a>>1)&0x7f)-((b>>1)&0x7f) );
#ifndef QT_NO_DEBUG
    assert(ret>=0);
    assert(ret<=0x7F);
#endif
    return (uint8_t)ret;
}

uint8_t pe_8bit_diff(uint8_t a, uint8_t b)
{
    int ret;
    ret=abs(a-b);
#ifndef QT_NO_DEBUG
    assert(ret>=0);
    assert(ret<=0xFF);
#endif
    return (uint8_t)ret;
}

uint8_t pe_2bit_diff_6bit_exor(uint8_t a, uint8_t b)
{
    int ret,upper_2bit,lower_6bit;
    upper_2bit=abs( ((a>>6)&0x3) - ((b>>6)&0x3) );
    lower_6bit=(a&0x3F) ^ (b&0x3F);
    ret=(upper_2bit<<6) | lower_6bit;
#ifndef QT_NO_DEBUG
    assert(upper_2bit>=0);
    assert(upper_2bit<=0x3);
    assert(lower_6bit>=0);
    assert(lower_6bit<=0x3F);
    assert(ret>=0);
    assert(ret<=0xFF);
#endif
    return (uint8_t)ret;
}

uint8_t pe_3bit_diff_5bit_exor(uint8_t a, uint8_t b)
{
    int ret,upper_3bit,lower_5bit;
    upper_3bit=abs( ((a>>5)&0x7) - ((b>>5)&0x7) );
    lower_5bit=(a&0x1F) ^ (b&0x1F);
    ret=(upper_3bit<<5) | lower_5bit;
#ifndef QT_NO_DEBUG
    assert(upper_3bit>=0);
    assert(upper_3bit<=0x7);
    assert(lower_5bit>=0);
    assert(lower_5bit<=0x1F);
    assert(ret>=0);
    assert(ret<=0xFF);
#endif
    return (uint8_t)ret;
}

uint8_t pe_4bit_diff_4bit_exor(uint8_t a, uint8_t b)
{
    int ret,upper_4bit,lower_4bit;
    upper_4bit=abs( ((a>>4)&0xF) - ((b>>4)&0xF) );
    lower_4bit=(a&0xF) ^ (b&0xF);
    ret=(upper_4bit<<4) | lower_4bit;
#ifndef QT_NO_DEBUG
    assert(upper_4bit>=0);
    assert(upper_4bit<=0xF);
    assert(lower_4bit>=0);
    assert(lower_4bit<=0xF);
    assert(ret>=0);
    assert(ret<=0xFF);
#endif
    return (uint8_t)ret;
}

uint8_t pe_5bit_diff_3bit_exor(uint8_t a, uint8_t b)
{
    int ret,upper_5bit,lower_3bit;
    upper_5bit=abs( ((a>>3)&0x1F) - ((b>>3)&0x1F) );
    lower_3bit=(a&0x7) ^ (b&0x7);
    ret=(upper_5bit<<3) | lower_3bit;
#ifndef QT_NO_DEBUG
    assert(upper_5bit>=0);
    assert(upper_5bit<=0x1F);
    assert(lower_3bit>=0);
    assert(lower_3bit<=0x7);
    assert(ret>=0);
    assert(ret<=0xFF);
#endif
    return (uint8_t)ret;
}

uint8_t pe_6bit_diff_2bit_exor(uint8_t a, uint8_t b)
{
    int ret,upper_6bit,lower_2bit;
    upper_6bit=abs( ((a>>2)&0x3F) - ((b>>2)&0x3F) );
    lower_2bit=(a&0x3) ^ (b&0x3);
    ret=(upper_6bit<<2) | lower_2bit;
#ifndef QT_NO_DEBUG
    assert(upper_6bit>=0);
    assert(upper_6bit<=0x3F);
    assert(lower_2bit>=0);
    assert(lower_2bit<=0x3);
    assert(ret>=0);
    assert(ret<=0xFF);
#endif
    return (uint8_t)ret;
}


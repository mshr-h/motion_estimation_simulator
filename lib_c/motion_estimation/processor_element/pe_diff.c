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

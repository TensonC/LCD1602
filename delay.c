#include "delay.h"
#include <intrins.h>

volatile void delay_ms(unsigned char ms)
{
    unsigned char i, j;

    while (ms--)
    {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
    }
    
}
volatile void delay_us(unsigned char us)
{
    while (us--)
    {
        _nop_();
    }
    
}
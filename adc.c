#include<lpc21xx.h>
#include"header.h"

void adc_init(void)
{
PINSEL1|=15400000;
ADCR|=00200400;
}

#define DONE ((ADDR>>31)&1)
u32 adc_read(u8 ch_num)
{
u32 result;
ADCR|=1<<ch_num;
ADCR|=1<<24;
while(DONE==0);
ADCR^=1<<24;
ADCR^=1<<ch_num;
result=(ADDR>>6)&0x3ff;
return result; 
}

#include<lpc21xx.h>
#include"header.h"

void lcd_data(u8 data)
{
// HIGHER NIBBLE
IOCLR1=0XFE<<16;
IOSET1=(data&0xf0)<<16;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
// LOWER NIBBLE
IOCLR1=0XFE<<16;
IOSET1=(data&0X0F)<<20;
IOSET1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_cmd(u8 cmd)
{
IOCLR1=0XFE<<16;
IOSET1=(cmd&0XF0)<<16;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
IOCLR1=0XFE<<16;
IOSET1=(cmd&0X0F)<<20;
IOCLR1=1<<17;
IOCLR1=1<<18;
IOSET1=1<<19;
delay_ms(2);
IOCLR1=1<<19;
}

void lcd_init(void)
{
PINSEL1|=0xfe<<16;
IOCLR1=1<<19;
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x0e);
lcd_cmd(0x01);
}

void lcd_string(s8 *p)
{
while(*p)
{
lcd_data(*p);
p++;
}
}

void lcd_integer(s32 n)
{
s32 a[20],i=0;
if(n==0)
{
lcd_data('0');
}
else if(n<0)
{
n=-n;
lcd_data('-');
}
while(n>0)
{
a[i++]=n%10+48;
n=n/10;
}
for(i=i-1;i>=0;i--)
lcd_data(a[i]);
}

void lcd_float(float f)
{
s32 n;
if(f==0)
lcd_string("0.0");
else if(f<0)
{
f=-f;
lcd_data('-');
}
n=f;
lcd_integer(n);
n=(f-n)*100000;
lcd_data('.');
lcd_integer(n);
}

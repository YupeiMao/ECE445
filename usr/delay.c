//延时模块
#include "delay.h"

void delay_ms(unsigned int t)//延时1ms
{
	 unsigned int x;
	unsigned char y;
	for(x=t;x>0;x--)
		for(y=255;y>0;y--); 
	
}

void delay_us(unsigned char i)//延时1us
{
 while(i--);
}
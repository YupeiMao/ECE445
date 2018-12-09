#ifndef __DELAY_H__ 
#define __DELAY_H__

void  Delay_Ms(u16 t);
void  Delay_Us(u8 i);//ÑÓÊ±1us

void Delay_Us(u8 i)//ÑÓÊ±1us
{
	while(i--)
	{
		_nop_();
    _nop_();
	}
}

void Delay_Ms(u16 t)//ÑÓÊ±1ms
{
	u16 i;
	while(t--)
	{
		for(i=110;i>0;i--);
	}
}



#endif

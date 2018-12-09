#ifndef KEY_H
#define KEY_H

//#define KEY_H1    P00

#define KEY_S1    P55			//enter
#define KEY_S2    P15			//+
#define KEY_S3    P14			//-
#define KEY_S4    P13			//ecs

//#define KEY_S1    P45			//enter
//#define KEY_S2    P46			//+
//#define KEY_S3    P76			//-
//#define KEY_S4    P77			//ecs

#define KEY_OK      0x01
#define KEY_INC     0x02
#define KEY_DEC     0x03
#define KEY_ESC     0x04

#define KEY_TIM_MAX 5

u8 key_scan_matrix(void)
{
//	KEY_H1 = 0;
	if(KEY_S1==0)
	{
		Delay_Ms(KEY_TIM_MAX);
		if(KEY_S1==0)
		{
			return KEY_OK;
		}
	}
	else if(KEY_S2==0)
	{
		Delay_Ms(KEY_TIM_MAX);
		if(KEY_S2==0)
		{
			return KEY_INC;
		}
	}
	else if(KEY_S3==0)
	{
		Delay_Ms(KEY_TIM_MAX);
		if(KEY_S3==0)
		{
			return KEY_DEC;
		}
	}
	else if(KEY_S4==0)
	{
		Delay_Ms(KEY_TIM_MAX);
		if(KEY_S4==0)
		{
			return KEY_ESC;
		}
	}
	return 0xff;
}

u8 Func_Get_Push_Key_Val(void)
{
	static u8 key_val_buf = 0;
	u8 key_val = key_scan_matrix();
	if(key_val_buf != key_val)
	{
		key_val_buf = key_val;
		if(key_val!=0xff)
		{
			return key_val;
		}	
	}
	return 0xff;		
}

#endif

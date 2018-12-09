#ifndef BEEP_H
#define BEEP_H

#define O3_Port    P20
#define A_Port     P21
#define B_Port     P22
#define C_Port     P23
#define D_Port     P24

#define Led_Port1  P42
#define Led_Port2  P41
#define Beep_Port  P44

void Tec1_Ctrl(u8 tec)
{
	if(tec==0)
	{
		A_Port = 0;
		B_Port = 0;
	}
	else
	{
		A_Port = 0;
		B_Port = 1;
	}
}
void Tec2_Ctrl(u8 tec)
{
	if(tec==0)
	{
		C_Port = 0;
		D_Port = 0;
	}
	else
	{
		C_Port = 0;
		D_Port = 1;
	}
}
void o3_Ctrl(u8 o3)
{
	if(o3)O3_Port = 1;
	else O3_Port = 0;
}
void Led1_Ctrl(u8 led)
{
	if(led==0)Led_Port1 = 1;
	else Led_Port1 = 0;
}
void Led2_Ctrl(u8 led)
{
	if(led==0)Led_Port2 = 1;
	else Led_Port2 = 0;
}
void SBeep(u8 beep)
{
	if(beep==0)Beep_Port = 0;
	else Beep_Port = 1;
}

void Start_Beep(void)
{
	Beep_Port = 1;
	Delay_Ms(200);
	Beep_Port = 0;
	Delay_Ms(200);
	Beep_Port = 1;
	Delay_Ms(200);
	Beep_Port = 0;
}
#endif
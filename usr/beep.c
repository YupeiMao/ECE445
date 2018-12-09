/****************************************************************
*Function:	·äÃùÆ÷²Ù×÷
*Author:	Valerian
*Date:		2012/4/13
*Version:	1.0
*
****************************************************************/

#include "beep.h"
#include "config.h"
#include "delay.h"

void Start_Beep(void)
{
	if(Sound_ENB == 1)
	{
		Beep_Port = 0;
		delay_ms(80);
		Beep_Port = 1;
		delay_ms(80);
		Beep_Port = 0;
		delay_ms(80);
		Beep_Port = 1;
	}
}

void SBeep(void)
{
	if(Sound_ENB == 1)
	{
		Beep_Port = 0;
		delay_ms(20);
		Beep_Port = 1;
	}
}

void Error_Beep(void)
{
  if(Sound_ENB == 1)
	{
		Beep_Port = 0;
		delay_ms(5);
		Beep_Port = 1;
		delay_ms(5);
		Beep_Port = 0;
		delay_ms(5);
		Beep_Port = 1;
	}
}


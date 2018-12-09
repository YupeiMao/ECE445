#ifndef __LED_H__
#define __LED_H__

#include "STC15F2K60S2.h"	//STC15W4K48S4 专用头文件
#include "intrins.h"
#include "delay.h"

void Led_Ctrl(void);
void Led_On(unsigned char led);
void Led_Off(unsigned char led);
void Led_On_All(void);
void Led_Off_All(void);

void Led_off_InOuCaSa();
void Led_off_menu();
#endif


#include "config.h"
#include "key.h"
#include "led.h"


#define LED_PORT   P0

sbit CP1 = P2^1;
sbit CP2 =  P2^2;

const unsigned char LED_N[8] =   {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
//const unsigned char LED_N_6[6] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04};
//const unsigned char LED_N_2[8] =   {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};


/*********************  2颗芯片  *********************/
unsigned char HC574_1 = 0xff;
unsigned char HC574_2 = 0xff;

void led_on_low(unsigned char led);
void led_off_low(unsigned char led);

unsigned char code led_table[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};

void Led_Ctrl(void)
{
	if(key_left_val  != 0xFF)return;
	if(key_right_val != 0xFF)return;
	LED_PORT = 0XFF;
	if(LED_PORT != 0XFF)return;
	
	LED_PORT = HC574_1;
	if(LED_PORT == HC574_1)
	{
		CP1 = 0;
		CP1 = 1;
	}
	
	LED_PORT = HC574_2;
	if(LED_PORT == HC574_2)
	{
		CP2 = 0;
		CP2 = 1;
	}	
}

void Led_On(unsigned char led)
{
	if(led>=1&&led<=9)
			led_on_low(led_table[led]);
	else if(led == 10)
		HC574_1 &= ~0x01;
	else if(led>=11&&led<=18)
		led_on_low(led_table[led-1]);
}

void Led_Off(unsigned char led)
{
	led_off_low(led_table[led-1]);
}

void led_on_low(unsigned char led)
{
	if(led<=8 && led>=1)
	{
		HC574_1 &= ~LED_N[led-1];
	}
		else if(led>=9 && led<=16)
	{
		HC574_2 &= ~LED_N[led-9];
	}
	else if(led==17)
	{
		P61 = 0;			//ctrl按键对应的灯
	}
	else if(led==18)
	{
		P62 = 0;			//ok按键对应的灯
	}
}

void led_off_low(unsigned char led)
{
	if(led<=8 && led>=1)
	{
		HC574_1 |= ~LED_N[led-1];
	}
	
	else if(led>=9 && led<=16)
	{
		HC574_2 |= ~LED_N[led-9];
	}
	else if(led==17)
	{
		P61 = 1;			//ctrl按键对应的灯
	}
		else if(led==18)
	{
		P62 = 1;			//ok按键对应的灯
	}
}

void Led_On_All(void)
{
	HC574_1 = 0x00;
	HC574_2 = 0x00;
	P61 = 0;
	P62 = 0;
}

//void Led_Off_All(void)
//{
//	HC574_1 = 0xff;
//	HC574_2 = 0xff;
//	
//	P61 = 1;
//	P62 = 1;
//}
void Led_Off_All(void)	//关闭除IN、OUT、CALL、SAVE四个键以外的所有灯
{
	HC574_1 = 0xff;
	HC574_2 |= 0x63;
	
	P61 = 1;
	P62 = 1;
}

void Led_off_InOuCaSa()	//关闭矷N、OUT、CALL、SAVE四个键的灯
{
	HC574_2 |= (~0x63);
}



void Led_off_menu()
{
	HC574_2 |= 0x20;
}




#include "include.h"

m_TypeDef m_para =
{
	0,//u8  uart_recv_timout;
	0,//u16 uart_cnt;
	{0},//u8  uart_Buf[Uart_Buffer_Size];
	0,//u16 uart_dat_len;
	{0},//u8  uart_dat[Uart_Buffer_Size];
	25,//u8  temp_h;
	20,//	u8  temp_l;
	60,//	u8  rhum_h;
	20,//	u8  rhum_l;
	1,//  u8  o3_tim_m;
	0,//	u8  o3_tim_s;
	0,//u16 o3_tim;
};

void Mcu_Pin_Init(void);
void Timer_Init(void);
void IE_Init(void);

void main(void)
{	
	u8 key_val,reflash=0,set_flag = 0;
	
	u16 T,RH,B1;
	u8 lcd_buf[17]={0},cnt=0,temp;
	u8 second_r = 0;
	Mcu_Pin_Init();

	Start_Beep();
	
	System_Para_Get();
	
	Lcd_Init();
	
  DS1302_SetTime(0,18,11,13,2,8,0,0);//设置初始时间
	
	SHT2x_init();
	SHT2x_Resolution();
	B1 = SHT2x_user_register();
	
	MenuListInit();
	
	Timer_Init();
	
//	IE_Init();

	UART_Init();
	
	while(1)
	{			
		key_val = Func_Get_Push_Key_Val();
		if(key_val!=0xff)
		{
			if((set_flag)&&(key_val == KEY_ESC)&&(GetCurMenuID()<10))
			{
				set_flag = 0;
				Func_LCD_Init_Screen();
			}
			else if(key_val == KEY_OK && set_flag == 0) 
			{
				set_flag = 1;
				MenuShow();
			}
			else if(set_flag) 
			{
				MenuLoop(key_val);
			}
			else if(key_val == KEY_INC && set_flag == 0) 
			{
				if(m_para.o3_tim==0)
				{
					m_para.o3_tim = m_para.o3_tim_m;
					m_para.o3_tim = m_para.o3_tim*60 + m_para.o3_tim_s;
					m_para.o3_tim = m_para.o3_tim*2;
				}
			}
		}
		
		if(m_para.o3_tim)
		{
			o3_Ctrl(1);
			Led2_Ctrl(1);
//			Tec1_Ctrl(2);
//			Tec2_Ctrl(2);
		}
		else
		{
			o3_Ctrl(0);
			Led2_Ctrl(0);
//			Tec1_Ctrl(0);
//			Tec2_Ctrl(0);
		}
		
		if(set_flag==0)
		{
			DS1302_GetTime(&m_year,&m_month,&m_day,&m_week,&m_hour,&m_minute,&m_second);//读取当前时间
			if(second_r!=m_second)
			{
				second_r = m_second;
				T = T_Result();
				RH = RH_Result();
				if((T/100)<m_para.temp_l)
				{
					Tec1_Ctrl(1);
				}
				else
				{
					Tec1_Ctrl(0);
				}
				if((RH/100)>m_para.rhum_h)
				{
					
					Tec2_Ctrl(1);
				}
				else
				{
					Tec2_Ctrl(0);
				}
				if(((T/100)<m_para.temp_l)||((RH/100)>m_para.rhum_h))
				{
					Led1_Ctrl(1);
				}
				else
				{
					Led1_Ctrl(0);
				}
				cnt = 0;
				temp = m_year; 
				lcd_buf[cnt++]=temp/10%10+'0';
				lcd_buf[cnt++]=temp%10+'0';
				lcd_buf[cnt++]='-';
				temp = m_month;
				lcd_buf[cnt++]=temp/10%10+'0';
				lcd_buf[cnt++]=temp%10+'0';
				lcd_buf[cnt++]='-';
				temp = m_day;
				lcd_buf[cnt++]=temp/10%10+'0';
				lcd_buf[cnt++]=temp%10+'0';
				lcd_buf[cnt++]=' ';
				if(T>10000)lcd_buf[cnt++]=T/10000+'0';
				else lcd_buf[cnt++]=' ';
				if(T>1000)lcd_buf[cnt++]=T%10000/1000+'0';
				else lcd_buf[cnt++]=' ';
				lcd_buf[cnt++]=T%1000/100+'0';
				lcd_buf[cnt++]='.';
				lcd_buf[cnt++]=T%100/10+'0';
				lcd_buf[cnt++]=0xdf;
				lcd_buf[cnt++]='C';
				lcd_buf[cnt++]=0;
				Func_LCD_RowClearWriteString16(1,1,lcd_buf);
				cnt = 0;
				temp = m_hour;
				lcd_buf[cnt++]=temp/10%10+'0';
				lcd_buf[cnt++]=temp%10+'0';
				lcd_buf[cnt++]=':';
				temp = m_minute;
				lcd_buf[cnt++]=temp/10%10+'0';
				lcd_buf[cnt++]=temp%10+'0';
				lcd_buf[cnt++]=':';
				temp = m_second;
				lcd_buf[cnt++]=temp/10%10+'0';
				lcd_buf[cnt++]=temp%10+'0';
				lcd_buf[cnt++]=' ';
				if(RH>1000)lcd_buf[cnt++]=RH%10000/1000+'0';
				else lcd_buf[cnt++]=' ';
				lcd_buf[cnt++]=RH%1000/100+'0';
				lcd_buf[cnt++]='.';
				lcd_buf[cnt++]=RH%100/10+'0';
				lcd_buf[cnt++]='%';
				lcd_buf[cnt++]='R';
				lcd_buf[cnt++]='H';
				lcd_buf[cnt++]=0;
				Func_LCD_RowClearWriteString16(2,1,lcd_buf);
			}
		}
	}
}


void Mcu_Pin_Init(void)
{
	P0M1 = 0;
	P0M0 = 0;
	
	P1M1 = 0x00;
	P1M0 = 0x05;

	P2M1 = 0;
	P2M0 = 0xFF;

	P3M1 = 0;
	P3M0 = 0;
	
	P4M1 = 0;
	P4M0 = 0x16;
	
	P5M1 = 0;
	P5M0 = 0;
	
	KEY_S1 = 1;KEY_S2 = 1;KEY_S3 = 1;KEY_S4 = 1;
	
	SBeep(0);
	o3_Ctrl(0);
	Tec1_Ctrl(0);
	Tec2_Ctrl(0);
	Led1_Ctrl(0);
	Led2_Ctrl(0);
}

void Timer_Init(void)	//10微秒@27.000MHz
{
	EA = 0;

	AUXR |= 0x04;		//定时器时钟1T模式
	T2H = 0xA9; 			//11.0592M 2Ms
	T2L	= 0x9A;				//	
	AUXR |= 0x10;			//			相当于	TR2 = 1; 
	IE2  |= 0x04; 		//			相当于	ET2 = 1; 
}


u16 Timer2_Sec_Temp = 0;   //Timer2计数变量
Timer2_interrupt(void) interrupt 12  // 定时器1中断  (用于轮询)//没有发现那里用到
{                                    //非轮巡，用于为串口1定时//没用
	if(m_para.uart_cnt)
	{
		if(m_para.uart_recv_timout<Uart_Timout_Max)
		{
			m_para.uart_recv_timout++;
		}
	}
	Timer2_Sec_Temp++;
	if(Timer2_Sec_Temp > DEFINE_TIM_LCD_REFLASH)
	{
		Timer2_Sec_Temp = 0;
		if(m_para.o3_tim)m_para.o3_tim--;
	}
}

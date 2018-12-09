#include "uart.h"
#include "config.h"
#include "2402.h"
#include "beep.h"
#include "code.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "STC15F2K60S2.h"	//STC15W4K48S4 专用头文件

volatile unsigned char uart_cnt = 0;

volatile unsigned char uart_delay = 0;
unsigned char RX_CNT_COPY = 0;
bit busy;

void uart_scan(void)
{
	if(uart_cnt)
	{	
		uart_delay++;
		if(uart_delay>25)
		{
			if(uart_cnt == RX_CNT_COPY)
			{				
				UART_Data_Process();
				
//							Func_Display_XingHao();////

					uart_cnt = 0;
					RX_CNT_COPY = 0;
			}
			else
			{
				RX_CNT_COPY = uart_cnt;
			}
		}		  
	}
}

void Inoutbuf_init(void)
{
	/*****************/
	chuankou = 1;		 //			
//	InOut_Buf[5] = 1;//初始化   输入输出通道		1 -> 6
	FUNCTION = 1;		//初始化		初始化信号源为  A（即音频）
/*****************/
}
void save_pre_successful()
{
   if((Received_Buffer[0]==0xff)&&(Received_Buffer[3]==11)&&(Received_Buffer[4]==11))	
   {
	    	Lcd_Display(1,1,"                        ",24);
	    	Lcd_Display(2,1,"        succeed         ",24);
		 Received_Buffer[3]=0;
		 Received_Buffer[4]=0;
   }
}

void Recevied_IDdisp()
{
	unsigned char buf[1];
	  if((Received_Buffer[0]==0xff)&&(Received_Buffer[3]==12)&&(Received_Buffer[4]==11))	
   {
			buf[0] = Received_Buffer[2];
		
			Lcd_Display(2,11,buf,1);
   }
}
void Recevied_precount_disp()
{
		unsigned char buf[2],temp;
	  if((Received_Buffer[0]==0xff)&&(Received_Buffer[1]==12)&&(Received_Buffer[2]=='*')&&(Received_Buffer[4]==11))	
   {
		 temp = Received_Buffer[3];
			buf[0] = temp/10 + '0';
		 	buf[1] = temp%10 + '0';
		  Lcd_Display(1,22,"PRL",3);
			Lcd_Display(2,23,buf,2);
   }
}

void UART_Data_Process(void)
{
	unsigned char i = 0,j=0,Check_Sum = 0;
	unsigned char Receive_Data_Len = 0;		   //数据包长度

	Receive_Data_Len = uart_cnt;
	
	for(j=i;j<Receive_Data_Len-i;j++)////////////
	{
		Received_Buffer[j-i] = Received_Buffer[j]; 
	}
	
 	Receive_Data_Len = Receive_Data_Len-1;////////
	
	switch(Received_Buffer[2])
	{
		case 0x01:
				if(Receive_Data_Len==37&&In_Count&&Out_Count)//这里接受的是拿来改变最大输出和输入路数的
				{
					In_Count  = Received_Buffer[3];//主板的初始化里面发过来
					Out_Count = Received_Buffer[4];
					
					for(i=0;i<16;i++)
					{
						Xinghao1[i+3] = Received_Buffer[5+i];	//接收第一行字符显示
					}
					
					for(i=0;i<16;i++)
					{
//						Xinghao[i+3] = Received_Buffer[5+i+16];//接收设备型号
						Xinghao[i+3] = Received_Buffer[5+i+16];//接收设备型号
					}
					
//					for(i=0;i<16;i++)
//					{
//						Xinghao[i+3] = Received_Buffer[5+i];//接收设备型号
//					}
					
					flag_xinghao_update = 1;
					get_xinh = 1;
				}
			break;
		case 0x02: 
				if(Receive_Data_Len==(3+Out_Count)) //这里数直接接受几路用于显示的（切换）
				{								
					for(i=0;i<Out_Count;i++)
					{
						InOut_Buf[i] = Received_Buffer[3+i];
					}					
			  }   							
        chuankou=1;	
				y++;
			break;
		case 0x03:	
				if(Received_Buffer[3]==0x01)SBeep();
				else Error_Beep();
			break;
		default:
			break;
	}
	
		switch(Received_Buffer[1])      // DEFINE_FUNCTION_A 0X01    DEFINE_FUNCTION_G 0X04    DEFINE_FUNCTION_V 0X02                                
	{
    case 0XE1:FUNCTION=1;break;
		case 0XE2:FUNCTION=2;break;
		case 0XE3:FUNCTION=3;break;
		case 0XE4:FUNCTION=4;break;
		case 0XE5:FUNCTION=5;break;
		case 0XE6:FUNCTION=6;break;
		case 0XE7:FUNCTION=7;break;
		case 0XE0:FUNCTION=0;break;

		default:break;
  }
}

void UART_Init(void)
{
	EA = 0;        
	
	PCON |= 0x80;		//波特率不倍速  SMOD的控制
	SCON = 0x50;		//8位数据，可变波特率
	
//	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T（传统8051速率）
	AUXR |= 0x40;//0xDF;
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD |= 0x20;		//定时器1为8位自动重装模式
	TL1 = 0xFA;//0xFD;		//定时器初值
	TH1 = 0xFA;//0xFD;		//	
		
	ET1 = 0; 				//关闭Timer1中断
	TR1 = 1;        //启动定时器T1 			   
	
	ES=1;           //允许串行口中断
	EA =1;          //单片机中断允许 
}

void UART_Send_One(unsigned char Data)
{
	while(busy);
	busy = 1;
	SBUF = Data;  //发送数据
	
}

void UART_Send(unsigned char* Data, unsigned int len)
{
	while(len--)
	{
		UART_Send_One(*Data); 
		Data++;	
	}
}
//-------------------------------------------------------------------------------------------------- 
// 函数名称： com_interrup()串口接收中断处理函数 
// 函数功能： 接收包括起始位’S’在内的十位数据到数据缓冲区 
//-------------------------------------------------------------------------------------------------- 
 void com_interrupt(void) interrupt 4  // using 3   //串口中断
{
		unsigned char Recived_Temp = 0;
//	ES = 0;
	if(RI) 
	{
		if(uart_cnt<Buffer_Size)
		{
			uart_delay = 0;
			Received_Buffer[uart_cnt++] = SBUF; 			
		}
		RI=0;   	
	}
	if(TI)                                   //处理发送中断 
	{
		TI=0;
		busy = 0;
	}
//	ES = 1;
}


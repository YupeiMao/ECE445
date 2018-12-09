#include "uart.h"
#include "config.h"
#include "2402.h"
#include "beep.h"
#include "code.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "STC15F2K60S2.h"	//STC15W4K48S4 ר��ͷ�ļ�

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
//	InOut_Buf[5] = 1;//��ʼ��   �������ͨ��		1 -> 6
	FUNCTION = 1;		//��ʼ��		��ʼ���ź�ԴΪ  A������Ƶ��
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
	unsigned char Receive_Data_Len = 0;		   //���ݰ�����

	Receive_Data_Len = uart_cnt;
	
	for(j=i;j<Receive_Data_Len-i;j++)////////////
	{
		Received_Buffer[j-i] = Received_Buffer[j]; 
	}
	
 	Receive_Data_Len = Receive_Data_Len-1;////////
	
	switch(Received_Buffer[2])
	{
		case 0x01:
				if(Receive_Data_Len==37&&In_Count&&Out_Count)//������ܵ��������ı�������������·����
				{
					In_Count  = Received_Buffer[3];//����ĳ�ʼ�����淢����
					Out_Count = Received_Buffer[4];
					
					for(i=0;i<16;i++)
					{
						Xinghao1[i+3] = Received_Buffer[5+i];	//���յ�һ���ַ���ʾ
					}
					
					for(i=0;i<16;i++)
					{
//						Xinghao[i+3] = Received_Buffer[5+i+16];//�����豸�ͺ�
						Xinghao[i+3] = Received_Buffer[5+i+16];//�����豸�ͺ�
					}
					
//					for(i=0;i<16;i++)
//					{
//						Xinghao[i+3] = Received_Buffer[5+i];//�����豸�ͺ�
//					}
					
					flag_xinghao_update = 1;
					get_xinh = 1;
				}
			break;
		case 0x02: 
				if(Receive_Data_Len==(3+Out_Count)) //������ֱ�ӽ��ܼ�·������ʾ�ģ��л���
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
	
	PCON |= 0x80;		//�����ʲ�����  SMOD�Ŀ���
	SCON = 0x50;		//8λ���ݣ��ɱ䲨����
	
//	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T����ͳ8051���ʣ�
	AUXR |= 0x40;//0xDF;
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD |= 0x20;		//��ʱ��1Ϊ8λ�Զ���װģʽ
	TL1 = 0xFA;//0xFD;		//��ʱ����ֵ
	TH1 = 0xFA;//0xFD;		//	
		
	ET1 = 0; 				//�ر�Timer1�ж�
	TR1 = 1;        //������ʱ��T1 			   
	
	ES=1;           //�����п��ж�
	EA =1;          //��Ƭ���ж����� 
}

void UART_Send_One(unsigned char Data)
{
	while(busy);
	busy = 1;
	SBUF = Data;  //��������
	
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
// �������ƣ� com_interrup()���ڽ����жϴ����� 
// �������ܣ� ���հ�����ʼλ��S�����ڵ�ʮλ���ݵ����ݻ����� 
//-------------------------------------------------------------------------------------------------- 
 void com_interrupt(void) interrupt 4  // using 3   //�����ж�
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
	if(TI)                                   //�������ж� 
	{
		TI=0;
		busy = 0;
	}
//	ES = 1;
}


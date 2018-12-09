#ifndef __USART_H__
#define __USART_H__

void UART_Init(void);
void UART_Send_One(u8 Data);
void UART_Send(u8* Data, u8 len);

void UART_Data_Process(void)
{
	u16 i;
	m_para.uart_dat_len = m_para.uart_cnt;
	for(i=0;i<m_para.uart_dat_len;i++)////////////
	{
		m_para.uart_dat[i] = m_para.uart_Buf[i]; 
	}
	m_para.uart_cnt = 0;
}


void uart_scan(void)
{
	if(m_para.uart_recv_timout>=Uart_Timout_Max)
	{
		m_para.uart_recv_timout = 0;
		UART_Data_Process();
	}
}


void UART_Init(void)	//用的是串口一，引脚不去配置就默认在p30，p31上面
{
	EA = 0;        
	
	PCON |= 0x80;		//使能波特率倍速位SMOD
	SCON = 0x50;		//8位数据,可变波特率
#if 1
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
	TL1 = 0xF4;		//设定定时初值
	TH1 = 0xF4;		//设定定时器重装值
#else
	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T（传统8051速率）
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD |= 0x20;		//定时器1为8位自动重装模式
	TL1 = 0xFD;		//定时器初值
	TH1 = 0xFD;		//
#endif
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1		   
	
	ES=1;           //允许串行口中断
	EA =1;          //单片机中断允许 
}

void UART_Send_One(u8 Data)
{
	u8 t=0;
	SBUF = Data; 
  while(TI==0&&t<240)
	{
		t++;
	}
	TI  = 0;
  Delay_Us(200);
}

void UART_Send(u8* Data, u8 len)
{
	while(len--)
	{
		UART_Send_One(*Data); 
		Data++;	
	}
}
void com_interrupt(void) interrupt 4  // using 3   //串口中断
{
	if(RI) 
	{
		if(m_para.uart_cnt<Uart_Buffer_Size)
		{
			m_para.uart_recv_timout = 0;
			m_para.uart_Buf[m_para.uart_cnt++] = SBUF; 
		}
		RI=0;   	
	}
//	if(TI)                                 
//	{
//		TI=0;
//	}
}

#endif

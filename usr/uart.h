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


void UART_Init(void)	//�õ��Ǵ���һ�����Ų�ȥ���þ�Ĭ����p30��p31����
{
	EA = 0;        
	
	PCON |= 0x80;		//ʹ�ܲ����ʱ���λSMOD
	SCON = 0x50;		//8λ����,�ɱ䲨����
#if 1
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
	TL1 = 0xF4;		//�趨��ʱ��ֵ
	TH1 = 0xF4;		//�趨��ʱ����װֵ
#else
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T����ͳ8051���ʣ�
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD |= 0x20;		//��ʱ��1Ϊ8λ�Զ���װģʽ
	TL1 = 0xFD;		//��ʱ����ֵ
	TH1 = 0xFD;		//
#endif
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1		   
	
	ES=1;           //�����п��ж�
	EA =1;          //��Ƭ���ж����� 
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
void com_interrupt(void) interrupt 4  // using 3   //�����ж�
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

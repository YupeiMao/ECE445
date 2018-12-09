#ifndef __DS1302_H_
#define __DS1302_H_

sbit DS_SCLK = P1^0;                   //DS1302ʱ�ӿ�P1.0
sbit DS_IO   = P1^1;                   //DS1302���ݿ�P1.1
sbit DS_RST  = P1^2;                   //DS1302Ƭѡ��P1.2

u8 m_year,m_month,m_day,m_week,m_hour,m_minute,m_second;

/**************************************
��ʱX΢��
��ͬ�Ĺ�������,��Ҫ�����˺���
����ʱ������ʹ��1T��ָ�����ڽ��м���,�봫ͳ��12T��MCU��ͬ
**************************************/
void Delay()
{
    _nop_();
    _nop_();
}

/**************************************
��DS1302��1�ֽ�����
**************************************/
BYTE DS1302_ReadByte()
{
    BYTE i;
    BYTE dat = 0;
		P1M0 &= 0xFD;
		DS_IO = 1;
    for (i=0; i<8; i++)             //8λ������
    {
			DS_SCLK = 0;                   //ʱ��������
			Delay();                //��ʱ�ȴ�
			dat >>= 1;	                //��������һλ
			if (DS_IO) dat |= 0x80;        //��ȡ����
			DS_SCLK = 1;                   //ʱ��������
			Delay();                //��ʱ�ȴ�
		}
		P1M0 |= 0x2;
    return dat;
}

/**************************************
��DS1302д1�ֽ�����
**************************************/
void DS1302_WriteByte(BYTE dat)
{
    char i;

   for (i=0; i<8; i++)             //8λ������
    {
        DS_SCLK = 0;                   //ʱ��������
        Delay();                //��ʱ�ȴ�
        dat >>= 1;                  //�Ƴ�����
        DS_IO = CY;                    //�ͳ����˿�
        DS_SCLK = 1;                   //ʱ��������
        Delay();                //��ʱ�ȴ�
    }
}

/**************************************
��DS1302ĳ��ַ�ĵ�����
**************************************/
BYTE DS1302_ReadData(BYTE addr)
{
    BYTE dat;

    DS_RST = 0;
    Delay();
    DS_SCLK = 0;
    Delay();
    DS_RST = 1;
    Delay();
    DS1302_WriteByte(addr);         //д��ַ
    dat = DS1302_ReadByte();        //������
    DS_SCLK = 1;
    DS_RST = 0;

    return dat;
}

/**************************************
��DS1302��ĳ����ַд������
**************************************/
void DS1302_WriteData(BYTE addr, BYTE dat)
{
    DS_RST = 0;
    Delay();
    DS_SCLK = 0;
    Delay();
    DS_RST = 1;
    Delay();
    DS1302_WriteByte(addr);         //д��ַ
    DS1302_WriteByte(dat);          //д����
    DS_SCLK = 1;
    DS_RST = 0;
}

/**************************************
д���ʼʱ��
**************************************/
void DS1302_SetTime(u8 xg,u8 yr,u8 mn,u8 da,u8 wk,u8 hr,u8 mt,u8 sd)
{
	if((DS1302_ReadData(0xC1)==0XA5)&&(xg==0))return;
	DS1302_WriteData(0x8E,0x00);                 	//����д״̬�Ĵ��������֣�д�벻����ָ�� 
	DS1302_WriteData(0x80,((sd/10)<<4|(sd%10)));  //����д��Ĵ��������֣�д����ĳ�ʼֵ
	DS1302_WriteData(0x82,((mt/10)<<4|(mt%10)));  //����д�ּĴ��������֣�д��ֵĳ�ʼֵ
	DS1302_WriteData(0x84,((hr/10)<<4|(hr%10))); 	//����дСʱ�Ĵ��������֣�д��Сʱ�ĳ�ʼֵ
	DS1302_WriteData(0x86,((da/10)<<4|(da%10))); 	//����д�ռĴ��������֣�д���յĳ�ʼֵ
	DS1302_WriteData(0x88,((mn/10)<<4|(mn%10))); 	//����д�¼Ĵ��������֣�д���µĳ�ʼֵ
	DS1302_WriteData(0x8A,wk); 										//����д�ռĴ��������֣�д���յĳ�ʼֵ
	DS1302_WriteData(0x8c,((yr/10)<<4|(yr%10)));  //����д��Ĵ��������֣�д����ĳ�ʼֵ
	DS1302_WriteData(0xC0,0xA5);
	DS1302_WriteData(0x8E,0x80);
}

void DS1302_Set_Date(u8 yr,u8 mn,u8 da)
{
	DS1302_WriteData(0x8E,0x00);                 	//����д״̬�Ĵ��������֣�д�벻����ָ�� 
	DS1302_WriteData(0x86,((da/10)<<4|(da%10))); 	//����д�ռĴ��������֣�д���յĳ�ʼֵ
	DS1302_WriteData(0x88,((mn/10)<<4|(mn%10))); 	//����д�¼Ĵ��������֣�д���µĳ�ʼֵ
	DS1302_WriteData(0x8c,((yr/10)<<4|(yr%10)));  //����д��Ĵ��������֣�д����ĳ�ʼֵ
	DS1302_WriteData(0x8E,0x80);
}

void DS1302_Set_Time(u8 hr,u8 mt,u8 sd)
{
	DS1302_WriteData(0x8E,0x00);                 	//����д״̬�Ĵ��������֣�д�벻����ָ�� 
	DS1302_WriteData(0x80,((sd/10)<<4|(sd%10)));  //����д��Ĵ��������֣�д����ĳ�ʼֵ
	DS1302_WriteData(0x82,((mt/10)<<4|(mt%10)));  //����д�ּĴ��������֣�д��ֵĳ�ʼֵ
	DS1302_WriteData(0x84,((hr/10)<<4|(hr%10))); 	//����дСʱ�Ĵ��������֣�д��Сʱ�ĳ�ʼֵ
	DS1302_WriteData(0x8E,0x80);
}
/**************************************
��ȡ��ǰʱ��
**************************************/
void DS1302_GetTime(u8 *yr,u8 *mn,u8 *da,u8 *wk,u8 *hr,u8 *mt,u8 *sd)
{
  u8 ReadValue=0;
 	ReadValue = DS1302_ReadData(0x81);   		//����Ĵ���������
 	*sd=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	//����������ת��
	ReadValue = DS1302_ReadData(0x83);  		//�ӷּĴ�����
	*mt=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//����������ת��
	ReadValue = DS1302_ReadData(0x85);  		//��ʱ�Ĵ�����
	*hr=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//����������ת��
									             //����������ת��	
	ReadValue = DS1302_ReadData(0x87);  		//���ռĴ�����
	*da=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//����������ת��
	ReadValue = DS1302_ReadData(0x89);  		//���¼Ĵ�����
	*mn=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//����������ת��
	ReadValue = DS1302_ReadData(0x8B);  		//���ܼĴ�����
	*wk=ReadValue&0x0F; 
	ReadValue = DS1302_ReadData(0x8d);  		//����Ĵ�����
	*yr=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//����������ת��
}

/**************************************
��ʼ��DS1302
**************************************/
void DS1302_Initial()
{
    DS_RST = 0;
    DS_SCLK = 0;
    DS1302_WriteData(0x8e, 0x00);   //����д����
    DS1302_WriteData(0x80, 0x00);   //ʱ������
    DS1302_WriteData(0x90, 0xa6);   //һ�������ܣ�4K������
    DS1302_WriteData(0x8e, 0x80);   //д����
}

#endif
#include "ds18b20.h"
#include "delay.h"	
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
//��λDS18B20
void DS18B20_Rst(void)	   
{                 
	DS18B20_IO_OUT(); //SET PG11 OUTPUT
	DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(15);     //15US
  DS18B20_DQ_OUT=0; //����DQ
  delay_us(500);    //����750us
  DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(15);     //15US
}
//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
u8 DS18B20_Check(void) 	   
{   
	u8 retry=0;
	DS18B20_IO_IN();//SET PG11 INPUT	 
  while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		delay_us(1);
	}
	if(retry>=200)return 1;
	else retry=0;
  while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		delay_us(1);
	}
	if(retry>=240)return 1;	    
	return 0;
}
//��DS18B20��ȡһ��λ
//����ֵ��1/0
u8 DS18B20_Read_Bit(void) 			 // read one bit
{
  u8 data;
	DS18B20_IO_OUT();//SET PG11 OUTPUT
  DS18B20_DQ_OUT=0; 
	delay_us(2);
  DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();//SET PG11 INPUT
	delay_us(12);//12
	if(DS18B20_DQ_IN)data=1;
  else data=0;	 
  delay_us(50);//50          
  return data;
}
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
u8 DS18B20_Read_Byte(void)    // read one byte
{        
  u8 i,j,dat;
  dat=0;
	for (i=1;i<=8;i++) 
	{
		j=DS18B20_Read_Bit();
		dat=(j<<7)|(dat>>1);
  }						    
  return dat;
}
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_Write_Byte(u8 dat)     
{             
	u8 j;
	u8 testb;
	DS18B20_IO_OUT();//SET PG11 OUTPUT;
	for (j=1;j<=8;j++) 
	{
		testb=dat&0x01;
		dat=dat>>1;
		if(testb) 
		{
				DS18B20_DQ_OUT=0;// Write 1
				delay_us(2);                            
				DS18B20_DQ_OUT=1;
				delay_us(60); //60            
		}
		else 
		{
				DS18B20_DQ_OUT=0;// Write 0
				delay_us(60);//60             
				DS18B20_DQ_OUT=1;
				delay_us(2);                          
		}
  }
}
//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{ 
	DS18B20_Rst();	   
	DS18B20_Check();	 
	DS18B20_Write_Byte(0xcc);// skip rom
	DS18B20_Write_Byte(0x44);// convert
} 

//��ʼ�¶�ת��
void DS18B20_Convert(void)// ds1820 start convert
{
    DS18B20_Rst();	   
	  DS18B20_Check();	 
    DS18B20_Write_Byte(0xcc);// skip rom
    DS18B20_Write_Byte(0xbe);// convert
}
//��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
//����1:������
//����0:����    	 
u8 DS18B20_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOGʱ��

  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50MHz
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
 
 	DS18B20_Rst();
	return DS18B20_Check();
}  
//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
short DS18B20_Get_Temp(void)
{
	u8 temp;
	u8 TL,TH;
	short tem;
	OS_ERR err;
#if SYSTEM_SUPPORT_OS  
	OSIntEnter();    
#endif
	DS18B20_Start();  
	DS18B20_Convert();
#if SYSTEM_SUPPORT_OS  
	OSIntExit();    	//�˳��ж�
#endif	
	OSTimeDlyHMSM(0,0,0,10,OS_OPT_TIME_PERIODIC,&err);
#if SYSTEM_SUPPORT_OS  
	OSIntEnter();    
#endif
	TL=DS18B20_Read_Byte(); // LSB   
	TH=DS18B20_Read_Byte(); // MSB
#if SYSTEM_SUPPORT_OS  
	OSIntExit();    	//�˳��ж�
#endif	
	if(TH>7)
	{
		TH=~TH;
		TL=~TL; 
		temp=0;//�¶�Ϊ��  
	}
	else temp=1;//�¶�Ϊ��	  	  
	tem=TH; //��ø߰�λ
	tem<<=8;    
	tem+=TL;//��õװ�λ
	tem=(double)tem*0.625;//ת��     
	if(temp)return tem; //�����¶�ֵ
	else return -tem;    
}
















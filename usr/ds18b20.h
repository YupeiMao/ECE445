#ifndef __DS18B20_H__ 
#define __DS18B20_H__

#define DS18B20_IO  P40 

//��λDS18B20
void DS18B20_Rst(void)	   
{        
	DS18B20_IO=0; 
	Delay_Us(240);
	Delay_Us(240);
	DS18B20_IO=1; 
	Delay_Us(60);     
  Delay_Us(240);
	Delay_Us(180);
}

//��DS18B20��ȡһ���ֽ�
//����ֵ������������
u8 DS18B20_Read_Byte(void)    // read one byte
{        
  u8 i=0; 		//ÿ����������̵ĳ���ʱ��Ϊ60us������������֮�������1us���ϵĸߵ�ƽ�ָ���
	u8 dat=0; 
	for (i=8;i>0;i--) 		//һ���ֽ���8λ 
	{
		dat>>=1;
		DS18B20_IO=0;
		Delay_Us(1);
		DS18B20_IO=1;
		Delay_Us(1);
		if(DS18B20_IO)dat|=0x80;
		Delay_Us(60);
	} 
	return(dat);
}
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_Write_Byte(u8 dat)     
{             
	u8 i=0; 		//�����ߴӸߵ�ƽ�����͵�ƽ������д��ʼ�źš�15us֮�ڽ�����д��λ�͵��������ϣ�
	for(i=8;i>0;i--) 		//��15~60us֮��������߽��в���������Ǹߵ�ƽ��д1����д0������ 
	{
		DS18B20_IO = 0; 
		Delay_Us(1);
		DS18B20_IO = dat&0x01;
		dat>>=1;
		Delay_Us(60);
		DS18B20_IO=1;
		Delay_Us(1);
		
	} 
}
u8 DS18B20_Check(void) 	   
{   
	u8 retry=0; 
  while (DS18B20_IO&&retry<200)
	{
		retry++;
	}
	if(retry>=200)return 1;
	else retry=0;
  while (!DS18B20_IO&&retry<240)
	{
		retry++;
	}
	if(retry>=240)return 1;	    
	return 0;
}
//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{ 
	DS18B20_Rst();	
	DS18B20_Write_Byte(0xcc);// skip rom
	DS18B20_Write_Byte(0x44);// convert
} 

//��ʼ�¶�ת��
void DS18B20_Convert(void)// ds1820 start convert
{
	DS18B20_Rst();	
	DS18B20_Write_Byte(0xcc);// skip rom
	DS18B20_Write_Byte(0xbe);// convert
}

//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
int DS18B20_Get_Temp(void)
{
	u8 temp=1;
	u8 TL,TH;
	int tem;
	EA=0;
	DS18B20_Start();  
	DS18B20_Convert();
	EA=1;
	Delay_Ms(10);
	EA=0;
	TL=DS18B20_Read_Byte(); // LSB   
	TH=DS18B20_Read_Byte(); // MSB
	EA=1;
	if(TH>0x7f)
	{
		TH=~TH+1;
		TL=~TL; 
		temp=0;//�¶�Ϊ��  
	}
	else temp=1;//�¶�Ϊ��	
	
	tem = TL/16+TH*16; //��ø߰�λ  
	if(temp)return tem; //�����¶�ֵ
	else return -tem;    
}
#endif


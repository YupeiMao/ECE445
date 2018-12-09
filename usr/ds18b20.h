#ifndef __DS18B20_H__ 
#define __DS18B20_H__

#define DS18B20_IO  P40 

//复位DS18B20
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

//从DS18B20读取一个字节
//返回值：读到的数据
u8 DS18B20_Read_Byte(void)    // read one byte
{        
  u8 i=0; 		//每个读周期最短的持续时间为60us，各个读周期之间必须有1us以上的高电平恢复期
	u8 dat=0; 
	for (i=8;i>0;i--) 		//一个字节有8位 
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
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte(u8 dat)     
{             
	u8 i=0; 		//数据线从高电平拉至低电平，产生写起始信号。15us之内将所需写的位送到数据线上，
	for(i=8;i>0;i--) 		//在15~60us之间对数据线进行采样，如果是高电平就写1，低写0发生。 
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
//开始温度转换
void DS18B20_Start(void)// ds1820 start convert
{ 
	DS18B20_Rst();	
	DS18B20_Write_Byte(0xcc);// skip rom
	DS18B20_Write_Byte(0x44);// convert
} 

//开始温度转换
void DS18B20_Convert(void)// ds1820 start convert
{
	DS18B20_Rst();	
	DS18B20_Write_Byte(0xcc);// skip rom
	DS18B20_Write_Byte(0xbe);// convert
}

//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
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
		temp=0;//温度为负  
	}
	else temp=1;//温度为正	
	
	tem = TL/16+TH*16; //获得高八位  
	if(temp)return tem; //返回温度值
	else return -tem;    
}
#endif


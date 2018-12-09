#ifndef __DS1302_H_
#define __DS1302_H_

sbit DS_SCLK = P1^0;                   //DS1302时钟口P1.0
sbit DS_IO   = P1^1;                   //DS1302数据口P1.1
sbit DS_RST  = P1^2;                   //DS1302片选口P1.2

u8 m_year,m_month,m_day,m_week,m_hour,m_minute,m_second;

/**************************************
延时X微秒
不同的工作环境,需要调整此函数
此延时函数是使用1T的指令周期进行计算,与传统的12T的MCU不同
**************************************/
void Delay()
{
    _nop_();
    _nop_();
}

/**************************************
从DS1302读1字节数据
**************************************/
BYTE DS1302_ReadByte()
{
    BYTE i;
    BYTE dat = 0;
		P1M0 &= 0xFD;
		DS_IO = 1;
    for (i=0; i<8; i++)             //8位计数器
    {
			DS_SCLK = 0;                   //时钟线拉低
			Delay();                //延时等待
			dat >>= 1;	                //数据右移一位
			if (DS_IO) dat |= 0x80;        //读取数据
			DS_SCLK = 1;                   //时钟线拉高
			Delay();                //延时等待
		}
		P1M0 |= 0x2;
    return dat;
}

/**************************************
向DS1302写1字节数据
**************************************/
void DS1302_WriteByte(BYTE dat)
{
    char i;

   for (i=0; i<8; i++)             //8位计数器
    {
        DS_SCLK = 0;                   //时钟线拉低
        Delay();                //延时等待
        dat >>= 1;                  //移出数据
        DS_IO = CY;                    //送出到端口
        DS_SCLK = 1;                   //时钟线拉高
        Delay();                //延时等待
    }
}

/**************************************
读DS1302某地址的的数据
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
    DS1302_WriteByte(addr);         //写地址
    dat = DS1302_ReadByte();        //读数据
    DS_SCLK = 1;
    DS_RST = 0;

    return dat;
}

/**************************************
往DS1302的某个地址写入数据
**************************************/
void DS1302_WriteData(BYTE addr, BYTE dat)
{
    DS_RST = 0;
    Delay();
    DS_SCLK = 0;
    Delay();
    DS_RST = 1;
    Delay();
    DS1302_WriteByte(addr);         //写地址
    DS1302_WriteByte(dat);          //写数据
    DS_SCLK = 1;
    DS_RST = 0;
}

/**************************************
写入初始时间
**************************************/
void DS1302_SetTime(u8 xg,u8 yr,u8 mn,u8 da,u8 wk,u8 hr,u8 mt,u8 sd)
{
	if((DS1302_ReadData(0xC1)==0XA5)&&(xg==0))return;
	DS1302_WriteData(0x8E,0x00);                 	//根据写状态寄存器命令字，写入不保护指令 
	DS1302_WriteData(0x80,((sd/10)<<4|(sd%10)));  //根据写秒寄存器命令字，写入秒的初始值
	DS1302_WriteData(0x82,((mt/10)<<4|(mt%10)));  //根据写分寄存器命令字，写入分的初始值
	DS1302_WriteData(0x84,((hr/10)<<4|(hr%10))); 	//根据写小时寄存器命令字，写入小时的初始值
	DS1302_WriteData(0x86,((da/10)<<4|(da%10))); 	//根据写日寄存器命令字，写入日的初始值
	DS1302_WriteData(0x88,((mn/10)<<4|(mn%10))); 	//根据写月寄存器命令字，写入月的初始值
	DS1302_WriteData(0x8A,wk); 										//根据写日寄存器命令字，写入日的初始值
	DS1302_WriteData(0x8c,((yr/10)<<4|(yr%10)));  //根据写年寄存器命令字，写入年的初始值
	DS1302_WriteData(0xC0,0xA5);
	DS1302_WriteData(0x8E,0x80);
}

void DS1302_Set_Date(u8 yr,u8 mn,u8 da)
{
	DS1302_WriteData(0x8E,0x00);                 	//根据写状态寄存器命令字，写入不保护指令 
	DS1302_WriteData(0x86,((da/10)<<4|(da%10))); 	//根据写日寄存器命令字，写入日的初始值
	DS1302_WriteData(0x88,((mn/10)<<4|(mn%10))); 	//根据写月寄存器命令字，写入月的初始值
	DS1302_WriteData(0x8c,((yr/10)<<4|(yr%10)));  //根据写年寄存器命令字，写入年的初始值
	DS1302_WriteData(0x8E,0x80);
}

void DS1302_Set_Time(u8 hr,u8 mt,u8 sd)
{
	DS1302_WriteData(0x8E,0x00);                 	//根据写状态寄存器命令字，写入不保护指令 
	DS1302_WriteData(0x80,((sd/10)<<4|(sd%10)));  //根据写秒寄存器命令字，写入秒的初始值
	DS1302_WriteData(0x82,((mt/10)<<4|(mt%10)));  //根据写分寄存器命令字，写入分的初始值
	DS1302_WriteData(0x84,((hr/10)<<4|(hr%10))); 	//根据写小时寄存器命令字，写入小时的初始值
	DS1302_WriteData(0x8E,0x80);
}
/**************************************
读取当前时间
**************************************/
void DS1302_GetTime(u8 *yr,u8 *mn,u8 *da,u8 *wk,u8 *hr,u8 *mt,u8 *sd)
{
  u8 ReadValue=0;
 	ReadValue = DS1302_ReadData(0x81);   		//从秒寄存器读数据
 	*sd=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F);	//将读出数据转化
	ReadValue = DS1302_ReadData(0x83);  		//从分寄存器读
	*mt=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//将读出数据转化
	ReadValue = DS1302_ReadData(0x85);  		//从时寄存器读
	*hr=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//将读出数据转化
									             //将读出数据转化	
	ReadValue = DS1302_ReadData(0x87);  		//从日寄存器读
	*da=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//将读出数据转化
	ReadValue = DS1302_ReadData(0x89);  		//从月寄存器读
	*mn=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//将读出数据转化
	ReadValue = DS1302_ReadData(0x8B);  		//从周寄存器读
	*wk=ReadValue&0x0F; 
	ReadValue = DS1302_ReadData(0x8d);  		//从年寄存器读
	*yr=((ReadValue&0x70)>>4)*10 + (ReadValue&0x0F); 	//将读出数据转化
}

/**************************************
初始化DS1302
**************************************/
void DS1302_Initial()
{
    DS_RST = 0;
    DS_SCLK = 0;
    DS1302_WriteData(0x8e, 0x00);   //允许写操作
    DS1302_WriteData(0x80, 0x00);   //时钟启动
    DS1302_WriteData(0x90, 0xa6);   //一个二极管＋4K电阻充电
    DS1302_WriteData(0x8e, 0x80);   //写保护
}

#endif

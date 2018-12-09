#ifndef __sht20_H_
#define __sht20_H_

#define add_w 0x80   			  //传感器地址 + 写操作
#define add_r 0x81   			  //传感器地址 + 读操作
#define T_code 0xe3				  //温度测量指令 
#define RH_code 0xe5			  //湿度测量指令
#define user_code_w 0xe6		//用户寄存器写指令
#define user_code_r 0xe7		//用户寄存器读指令，可读电池电压是否小于2.25V
#define RST_code 0xfe			  // 软复位，寄存器服务


void SHT2x_init();
u8 SHT2x_user_register();
void SHT2x_Resolution();
bit SHT2x_battery();
u16 RH_Result();
u16 T_Result();


// 测量分辨率 RH 12BIT、T 14BIT，测量时间RH 29ms、T 85ms
// 测量分辨率 RH 8BIT、T 12BIT，测量时间RH 4ms、T 22ms
// SCL 时钟，延时2us
 
sbit sda=P3^3;	//数据线
sbit scl=P3^4;	//时钟线


void Delay1000ms(void)		// 1s  @22.1184MHz
{
	u8 i, j, k;

	_nop_();
	_nop_();
	i = 85;
	j = 12;
	k = 155;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void delay85ms(void)   //85ms   @22.1184MHz
{
  u8 i, j, k;
	_nop_();
	_nop_();
	i = 8;
	j = 37;
	k = 207;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
} 

void delay29ms(void)   //29ms   11.0592MHz
{
  u8 i, j, k;
	i = 3;
	j = 112;
	k = 240;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void delay15ms(void)   //15ms   11.0592MHz
{
  u8 i, j, k;

	_nop_();
	_nop_();
	i = 2;
	j = 67;
	k = 183;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void delay2us(void)   //2us   11.0592MHz
{
  u8 i;
	_nop_();
	_nop_();
	i = 8;
	while (--i);
}

void start(void)       //1 启动
{
	sda=1;
	delay2us();
	scl=1;
	delay2us();
	sda=0;
	delay2us();
	scl=0;
	delay2us();
}


void stop(void)       //2	停止
{
	sda=0;
	delay2us();
	scl=1;
	delay2us();
	sda=1;
	delay2us();
	scl=0;
	delay2us();
}


void ACK (void)       //3	 应答
{	
	sda=0;
	delay2us();

	scl=1;
	delay2us();		
	scl=0;
	delay2us();	 
}

void noACK (void)     //非应答
{
	scl=1;
	delay2us();
	sda=0;	
	scl=0;
	delay2us();
}


bit getACK(void)     //4	接受应答
{
	bit ack1=0;

	sda=1;
	delay2us();	
		   
	scl=1;
	delay2us();
	
	ack1=sda;

	scl=0;
	delay2us();

	return ack1;	
}


void send(u8 DATA)   //5 发送一字节
{
	u8 Bit_Counter=8;
	
	while(Bit_Counter>0) 
	{
		
		sda=(bit)(DATA&0x80);
		DATA<<=1;
				
		scl=1;
		delay2us();
		scl=0;
		delay2us();
			 		
		Bit_Counter--;
	}
	
}  


u8 Read()      //6	接受一字节
{
	u8 x=0,y=8;

	sda=1;

	while(y>0)
	{
		scl=1;
		delay2us();


		if(sda)
		x=x|0x01;
		else
		x=x&0xfe;
		

		scl=0;
		delay2us();
		
		if(y>1)			
		x=x<<1;

		y--;
	}

	return x;
}


void SHT2x_init()    // 1传感器初始化&软复位
{
	start();
	send(add_w);
	getACK(); 
	send(RST_code);
	getACK();
	stop(); 
	delay15ms();
	sda=1;
	scl=1;
}


u8 SHT2x_user_register()   // 2传感器用户寄存器读取
{
	u8 register_data;

	start();
	send(add_w);
	getACK(); 
	send(user_code_r);
	getACK(); 
			
	start();
	send(add_r);
	getACK();
	register_data=Read();
	noACK(); 
	stop();

	return register_data;
}


void SHT2x_Resolution()          // 3 传感器测量分辨率设置                                
{                                // 测量分辨率设置RH 8 BIT、T 12 BIT,测量时间 RH4ms、T22ms
	start();
	send(add_w);
	getACK(); 
	send(user_code_w);
	getACK();
	send(0x3b);
	getACK();
	getACK(); 
	stop();	
}



bit SHT2x_battery()             // 4传感器低电压检测
{                               // 此状态在每次测量后更新
	u8 battery;

	start();
	send(add_w);
	getACK(); 
	send(user_code_r);
	getACK(); 
			
	start();
	send(add_r);
	getACK();
	battery=Read();
	noACK(); 
	stop();

	battery=(battery&0x40)>>6;
	return battery;
}



/***********测量结果***********/

// 1 湿度测量
// 启动>>发送地址+写操作>>接受ACK>>湿度测量命令>>接受ACK>>启动>>发送地址+读操作>>接受ACK>>测量时间延时>>读取高位数据>>ACK>>读取地位数据>>NO_ACK>>停止
// 计算结果。返回结果
u16 RH_Result()   
{
	u16 RH_Data;
	u32 RH=0;	
	start();
	send(add_w);
	getACK(); 
	send(RH_code);
	getACK();	
	start();
	send(add_r);
	getACK();  
	delay29ms(); 
	RH_Data=Read();
	ACK();	  
	RH_Data=RH_Data<<8;  
	RH_Data=RH_Data|Read();
	noACK();
	stop();
		
	RH_Data=RH_Data&0xfffc;		
	RH=RH_Data*12500L;
	RH=RH>>16;
	RH=RH-600;

	return RH;
}

// 2 温度测量
// 启动>>发送地址+写操作>>接受ACK>>温度测量命令>>接受ACK>>启动>>发送地址+读操作>>接受ACK>>测量时间延时>>读取高位数据>>ACK>>读取地位数据>>NO_ACK>>停止
// 计算结果。返回结果

u16 T_Result()
{
	u16 T_Data;
	u32 T=0;	

	start();
	send(add_w);
	getACK(); 
	send(T_code);
	getACK(); 		
	start();
	send(add_r);
	getACK();  	 
	delay85ms();	

	T_Data=Read();
	ACK();	
	T_Data=T_Data<<8; 	   
	T_Data=T_Data|Read();
	noACK();
	stop();

	T_Data=T_Data&0xfffE;		
	T=T_Data*17572L;
	T=T>>16;
	T=T-4685;

	return T;
}  

#endif

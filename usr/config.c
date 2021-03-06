/****************************************************************
*Function:	初始化以及操作基本设备：串口、定时器、外部中断；端口初始化
*Author:	Valerian
*Date:		2012/4/13
*Version:	1.0
*
****************************************************************/

#include "config.h"
#include "eeprom.h"
#include "2402.h"
#include "uart.h"
#include "code.h"
#include "STC15F2K60S2.h"	//STC15W4K48S4 专用头文件


// unsigned char anjian = 1;
 unsigned char fuwei = 0;
// unsigned char flag = 0;
 unsigned char IR_BIAOZI=0;
 unsigned char MENU_BIAOZI=0;
// unsigned char out_num=0;
 
 unsigned char switch_disp = 0;
 unsigned char a = 1;
 unsigned char y = 0;
 unsigned char z = 0;
 

 
 unsigned char ch=1;
 unsigned char change_page=0;
 unsigned char fanye=0;
 unsigned char fanye1=0;
 unsigned char chuankou=0;
 unsigned char cleaing_out=0;
 unsigned char cleaing_in=0;
 unsigned char FUNCTION;
 unsigned char kkey=0;
/***********************************移植时需要修改的内容**************************/
unsigned char flag_xinghao_update = 0;
unsigned char get_xinh = 0;

unsigned char flag_lcd_update = 0;
unsigned char flag_key_in_out = 0;//1=in 2=out
unsigned char flag_key_Ctrl = 0;//1=in 2=out
unsigned char flag_press_ok = 0;
unsigned char flag_ok;
unsigned char flag_hold;
unsigned char all_switch;
unsigned char N_Fanye;
unsigned char flag_num_in = 0;
unsigned char flag_num_out = 0;
unsigned char flag_num_call = 0;
unsigned char flag_num_save = 0;
unsigned int  flag_pos_set = 0;
unsigned char flag_pos_call_save = CALL;
/****************************参数配置_START**********************************************/ 
//unsigned char Fun_Ini = 0x07;            //(功能初始化)移植需要修改****	  0x1A;  // 没用
unsigned char Switch_Function = 0x07;	  	// Function of switching              �//�//没用

//unsigned char Device_Status=0;
unsigned char Baut_Rate = 3;    //波特率选择  9600
unsigned char Baut_Rate_Q = 3;    //波特率选择  9600

unsigned char Device_ID = 0;//
unsigned char Sound_ENB = 1;        //蜂鸣器声音开启
unsigned char LCDS_Enable = 0;	//屏保使能
unsigned int lcd_saver_time = 0;

// #if hx0808
unsigned char Out_Count = 99;	  //输出数量
unsigned char In_Count = 99;			//输入数量
unsigned char InOut_Buf[100] = {0};
unsigned char InOut_Buf_R[100] = {0};

/********************全局变量定义*************************/
unsigned char Lock_Key = 0;       //锁键盘标志位 0表示没锁
unsigned char Lock_IR = 0;	     //锁遥控器标志位 0表示没锁
unsigned char Lock_Device = 0;	 //锁定设备
unsigned char ID_Pressed = 0;	    //遥控器ID键按下标志

//unsigned char ADDR_Temp = 0;
unsigned char idata Page = 0;
//unsigned char Comdelay = 1;

unsigned int  T_Temp=0;				 //定义计数周期临时Z变量
//unsigned char Count = 0;
unsigned int  Code_Data = 0; 	     //红外接收编码的临时值
unsigned int  Code_Data1 = 0; 		   //红外接收编码的第一字节
unsigned int  Code_Data2 = 0; 		 //红外接收编码的第二、三字节
unsigned char Code_Start_Flag = 0; //接收数据开始标志
unsigned char Data_Count =0; 
unsigned int  Blank_Count=0;
unsigned char Received_Buffer[Buffer_Size] = {0};   	//定义接收缓冲区 

unsigned char Receive_Data_Point = 0;        //定义接收数据个数指示变量 
//unsigned char Com_End =0;       //
//unsigned char Receive_Data_Len = 0;		   //数据包长度

//unsigned char COMRecived_Complete_Flag = 0;	 //数据包接收完成标志



volatile unsigned int Timer2_Sec_Temp = 0;   //Timer2计数变量
volatile unsigned int Sec_Count  = 0;	   //秒钟计数


/*************************轮询相关变量_START********************************/
unsigned char PRETPL_Count = 1;		//预案轮询计数
unsigned int PRETPL_STime = 1;		//

/*************************轮询相关变量_END********************************/

/*************************功能数组_START*********************************/

//unsigned char Temp[1]={0};		//临时变量
//unsigned char OutV[1]={0};
//unsigned char OutA[1]={0};
//unsigned char OutVGA[1]={0};

//unsigned char OutV_Tem[1]={0};
//unsigned char OutA_Tem[1]={0};
//unsigned char OutVGA_Tem[1]={0};

/************************功能数组_END************************************/

/**************************本文件内函数申明_START************************************/
void State_Send(void);
void COM_LSend(unsigned char *Data,unsigned char Length);
void Stor_ADDR(unsigned char ADDR_Data);
void Save_PRE_Time(unsigned char Data_H,unsigned char Data_L,unsigned char PreNo);
void Save_Flag(unsigned char Data_Temp1);


/**************************本文件内函数申明_END************************************/





void Port_Init(void)		//必须初始化端口
{
	P0M1 = 0;
	P0M0 = 0;
	
	P1M1 = 0;
	P1M0 = 0;

	P2M1 = 0;
	P2M0 = 0;

	P3M1 = 0;
	P3M0 = 0;
	
	P4M1 = 0;
	P4M0 = 0;
	
	P5M1 = 0;
	P5M0 = 0;
	
	P6M1 = 0;
	P6M0 = 0;
	
	P7M1 = 0;
	P7M0 = 0;
}



void Timer_Init(void)
{
  EA = 0;
	
	AUXR &= 0x7F;		//定时器时钟12T模式
////	TMOD &= 0xF0;		//???????
	TMOD |= 0x02;		//设置定时器为模式2  8位自动重装模式
	TL0 = 0xA4;		  //初值
	TH0 = 0xA4;		  //重载值
	TF0 = 0;		    //清除TF0标志
	TR0 = 1;		    //开启定时器0
	PT0 = 1;				//Timer中断的优先级高
	ET0 = 1;  			//允许Time0中断	
	
//	T2H = 0xB8; 			//11.0592M 双倍速时10Ms
//	T2L	= 0x00;				//	
//	AUXR |= 0x10;			//			相当于	TR2 = 1; 
//	IE2  |= 0x04; 		//			相当于	ET2 = 1; 
}

void IE_Init(void)
{
	
	EX0 = 0;			//  关闭外部中断0
	IT1 = 1;
	EX1= 1;			//  开外部中断1	
	
}

void Timer0_Interrupt(void) interrupt 1   //using 1 	   //定时器0中断
{
	T_Temp++;			       //定义计数周期临时变量
	Blank_Count++;
	if(T_Temp > 2200)	    /// 2160
	{
		TR0 = 0;			//关闭定时器0
		T_Temp = 0;
		Data_Count = 0;
		Code_Data = 0;
		Code_Data2 = 0;
		Code_Start_Flag = 0;
		Blank_Count = 0;
	}
}


void External_Interrupt(void) interrupt 2 		//外部中断1  （红外遥控）
{
	EX1 = 0;
	if(Code_Start_Flag)//红外接收数据开始
	{	 
		if(Blank_Count > 15 && Blank_Count < 25 )//1
		{
			Code_Data = Code_Data | 0x8000;
			Code_Data>>=1;		
			Data_Count++;
			T_Temp = 0;
		}  
		else if(Blank_Count > 5 && Blank_Count < 15 )//0
		{
						
			Code_Data = Code_Data & 0x7FFF;	
			Code_Data>>=1;	
			Data_Count++;	
			T_Temp = 0;
		}
		if(Data_Count == 16)
		{
			Code_Data1 = Code_Data;		
		}
		else if(Data_Count == 32)
		{
			Code_Data2 = Code_Data; 
			Code_Start_Flag = 0;
			TR0 = 0;   
			T_Temp = 0;
		}
	}
	else if(Blank_Count > 120 && Blank_Count < 150)//红外开始标志
	{
		Code_Data = 0;
		Code_Data1 = 0;
		Code_Data2 = 0;
		Data_Count = 0;	
		Code_Start_Flag = 1;
		T_Temp = 0;	
	}
	else if(Data_Count == 0 && Code_Start_Flag == 0)//定时器开始
	{
		TR0 = 1; 		
		T_Temp = 0;	
	}
	Blank_Count = 0;  

	EX1 = 1;	

}


//Timer2_interrupt(void) interrupt 12  // 定时器2中断  (用于轮询)
//{
//	Timer2_Sec_Temp++;
//	if(Timer2_Sec_Temp > 99)
//	{
//		Sec_Count++;
//		Timer2_Sec_Temp = 0;
//	}
//}


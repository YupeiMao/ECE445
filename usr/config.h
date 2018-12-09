#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <STC15F2K60S2.h>	//STC15W4K48S4 专用头文件
#include <intrins.h>     //调用_nop_()函数的头文件

/********************************变量类型重定义******************/
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

/***************************************************************/
// #define hx0801 1



/************************蜂鸣器端口定义_START*************************/

#define Beep_Port P63

/************************蜂鸣器端口定义_END***************************/

/************************红外端口定义_START***************************/

#define ICP_Port  P33

/***********************红外端口定义_END*****************************/


/**********************数字芯片控制接口定义_START*********************/ 

/*********************数字芯片控制接口定义_END************************/

/**********键盘端口定义(键盘使用74HC138 控制)_START*************************/

#define Key_V0  P01   //接74138 A0端口 
#define Key_V1  P10    //接74138 A1端口 
#define Key_V2  P12    //接74138 A2端口 
#define Key_V3  P14    //接74138 A2端口 

#define Key_H_All  P2   //指示灯端口
#define Key_H0  P02 
#define Key_H1  P00
#define Key_H2  P11
#define Key_H3  P13
#define Key_H4  P13
#define Key_H5  P15
#define Key_H6  P16
#define Key_H7  P17

/********************键盘端口定义(键盘使用74HC138 控制)_END******************************/



/*****************************************************************************************
*  参数配置（可针对不同的机型做相应修改）
*  参数配置（可针对不同的机型做相应修改）
*  参数配置（可针对不同的机型做相应修改）
*****************************************************************************************/


/****************************参数配置_START**********************************************/ 
/****************************参数配置_START**********************************************/ 
/****************************参数配置_START**********************************************/ 

#define Present_Count 32			//预案最大数量
#define TPL_Maxtime 30				//轮询最大时间（分钟）
#define LCD_Time 10	                 //定义屏保时间

#define ADDR0 0x2A          			  //定义设备名（相当于地址）
#define Buffer_Size 38              // 定义接收缓冲区大小


/**********************eeprom存储地址定义_START***********************/

#define VGA_Addr  0    			      //VGA数组地址 
#define Video_Addr  VGA_Addr+32 		      //V数组地址 
#define Audio_Addr Video_Addr+32    	      //A数组地址
#define Function_Addr Audio_Addr+32         //功能数组地址(功能，地址。。。) 

///功能值存储次序///
/// 0 | 1  |     2   |      3  	 |    4     |   5,6  |  7  	  |	  8   |   9  |   10 	|	11		|/////  
// Fun|ADDR|Baut_Rate|LCDS_Enable|TPL_Enable|TPL_Time|Lock_Key|Lock_IR|Ini_ed|PRETPL_ENB|Sound_ENB	|
                              
#define TPL_Fun_Addr Function_Addr+32    	  //轮询存储地址
#define TPL_Addr TPL_Fun_Addr+32    	      //轮询存储地址
#define PRETPL_Time_Addr TPL_Addr+32    	  //预案轮询时间存储开始
#define Preset_Addr PRETPL_Time_Addr+64   	                  //预案存储地址开始  


/***********************eeprom存储地址定义_END*****************************/


/****************************参数配置_END**********************************************/ 
/****************************参数配置_END**********************************************/ 
/****************************参数配置_END**********************************************/ 

#define IN    1
#define OUT   2
#define CALL  3
#define SAVE  4
#define MENU  5
#define CTRL  6
#define ESC   7
#define OK    8

// extern unsigned char anjian;
 extern unsigned char fuwei;
// extern unsigned char flag;
 extern unsigned char IR_BIAOZI;
 extern unsigned char MENU_BIAOZI;
// extern unsigned char out_num;
 extern unsigned char ch;
 extern unsigned char switch_disp;
 extern unsigned char a;
 extern unsigned char z;
 extern unsigned char y;

// extern unsigned bit get_xinh;
 extern unsigned char change_page;
 extern unsigned char fanye;
 extern unsigned char fanye1;
 extern unsigned char chuankou;
 extern unsigned char cleaing_out;
 extern unsigned char cleaing_in;
 extern unsigned char FUNCTION;
 extern unsigned char kkey;

extern unsigned char flag_lcd_update;
extern unsigned char flag_xinghao_update;
extern unsigned char get_xinh;
extern unsigned char flag_press_ok;//新添加
extern unsigned char flag_ok;
extern unsigned char flag_hold;
extern unsigned char all_switch;
extern unsigned char N_Fanye;

extern unsigned char flag_key_in_out;
extern unsigned char flag_key_Ctrl;
extern unsigned char flag_num_in;
extern unsigned char flag_num_out;
extern unsigned char flag_num_call;
extern unsigned char flag_num_save;
extern unsigned int  flag_pos_set;
extern unsigned char flag_pos_call_save;
/********************全局变量申明(定义在config.c文件中)——START*************************/
extern unsigned char Sound_ENB;        //蜂鸣器声音开启
extern unsigned int LCD_Sec;
extern unsigned int Sec_Count;	   //秒钟计数

//extern unsigned char System_Init_Flag;

extern unsigned char Lock_Key;	            //锁键盘标志位 0表示没锁
extern unsigned char Lock_IR;	               //锁遥控器标志位 0表示没锁
extern unsigned char Lock_Device;	           //锁定设备
extern unsigned char ID_Pressed;	           //遥控器ID键按下标志

//extern unsigned char ADDR_Temp;
extern unsigned char idata Page;
//extern unsigned char Comdelay;

extern unsigned int T_Temp;					 //定义计数周期临时变量
//extern unsigned  char Count;
extern unsigned int Code_Data; 	     //红外接收编码的临时值
extern unsigned int Code_Data1; 		 //红外接收编码的第一字节
extern unsigned int Code_Data2; 		 //红外接收编码的第二、三字节
extern unsigned char Data_Count; 
extern unsigned int Blank_Count;
extern unsigned char Code_Start_Flag;	 //接收数据开始标志


//extern unsigned char Fun_Ini;            //(功能初始化)移植需要修改****
extern unsigned char Switch_Function;		   // Function of switching

#define DEFINE_LCD_SAVER_TIME 12000
extern unsigned char LCDS_Enable;	                  //屏保使能
extern unsigned int  lcd_saver_time;

//extern unsigned char Device_Status;
extern unsigned char Baut_Rate;                //波特率选择
extern unsigned char Baut_Rate_Q;                //波特率选择

extern unsigned char Device_ID;

extern unsigned char Receive_Data_Point;       //定义接收数据个数指示变量 
//extern unsigned char Com_End;            	   //
//extern unsigned char COMRecived_Complete_Flag;	 //数据包接收完成标志
//extern unsigned char Receive_Data_Len;		   //数据包长度

extern unsigned char Out_Count;	    	//输出数量
extern unsigned char In_Count;				//输入数量
extern unsigned char InOut_Buf[];
extern unsigned char InOut_Buf_R[];

extern unsigned char Received_Buffer[];   			 //定义接收缓冲区 
      


/*************************轮询相关变量********************************/
extern unsigned char PRETPL_Count;		//预案轮询计数
extern unsigned int PRETPL_STime;		//


//extern unsigned char Temp[];		//临时变量
//extern unsigned char OutV[];
//extern unsigned char OutA[];
//extern unsigned char OutVGA[];

//extern unsigned char OutV_Tem[];
//extern unsigned char OutA_Tem[];
//extern unsigned char OutVGA_Tem[];

/********************全局变量申明(定义在config.c文件中)_END*************************/



/******************************基本硬件操作函数申明_START***************************/
extern void Inoutbuf_init(void);
extern void Port_Init(void);
extern void Timer_Init(void);
extern void IE_Init(void);

extern void TPL_Switch(void);
extern void PRETPL_Switch(void);

extern void delay(unsigned char ms);
extern bit lcd_bz();
extern void lcd_wcmd(unsigned char cmd);
extern void lcd_pos(unsigned char pos);
extern void lcd_wdat(unsigned char dat);
extern void lcd_init();





/******************************基本硬件操作函数申明_END*****************************/

#endif




/****************************************************************
*Function:	³õÊ¼»¯ÒÔ¼°²Ù×÷»ù±¾Éè±¸£º´®¿Ú¡¢¶¨Ê±Æ÷¡¢Íâ²¿ÖÐ¶Ï£»¶Ë¿Ú³õÊ¼»¯
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
#include "STC15F2K60S2.h"	//STC15W4K48S4 ×¨ÓÃÍ·ÎÄ¼þ


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
/***********************************ÒÆÖ²Ê±ÐèÒªÐÞ¸ÄµÄÄÚÈÝ**************************/
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
/****************************²ÎÊýÅäÖÃ_START**********************************************/ 
//unsigned char Fun_Ini = 0x07;            //(¹¦ÄÜ³õÊ¼»¯)ÒÆÖ²ÐèÒªÐÞ¸Ä****	  0x1A;  // Ã»ÓÃ
unsigned char Switch_Function = 0x07;	  	// Function of switching              ¡//¡//Ã»ÓÃ

//unsigned char Device_Status=0;
unsigned char Baut_Rate = 3;    //²¨ÌØÂÊÑ¡Ôñ  9600
unsigned char Baut_Rate_Q = 3;    //²¨ÌØÂÊÑ¡Ôñ  9600

unsigned char Device_ID = 0;//
unsigned char Sound_ENB = 1;        //·äÃùÆ÷ÉùÒô¿ªÆô
unsigned char LCDS_Enable = 0;	//ÆÁ±£Ê¹ÄÜ
unsigned int lcd_saver_time = 0;

// #if hx0808
unsigned char Out_Count = 99;	  //Êä³öÊýÁ¿
unsigned char In_Count = 99;			//ÊäÈëÊýÁ¿
unsigned char InOut_Buf[100] = {0};
unsigned char InOut_Buf_R[100] = {0};

/********************È«¾Ö±äÁ¿¶¨Òå*************************/
unsigned char Lock_Key = 0;       //Ëø¼üÅÌ±êÖ¾Î» 0±íÊ¾Ã»Ëø
unsigned char Lock_IR = 0;	     //ËøÒ£¿ØÆ÷±êÖ¾Î» 0±íÊ¾Ã»Ëø
unsigned char Lock_Device = 0;	 //Ëø¶¨Éè±¸
unsigned char ID_Pressed = 0;	    //Ò£¿ØÆ÷ID¼ü°´ÏÂ±êÖ¾

//unsigned char ADDR_Temp = 0;
unsigned char idata Page = 0;
//unsigned char Comdelay = 1;

unsigned int  T_Temp=0;				 //¶¨Òå¼ÆÊýÖÜÆÚÁÙÊ±Z±äÁ¿
//unsigned char Count = 0;
unsigned int  Code_Data = 0; 	     //ºìÍâ½ÓÊÕ±àÂëµÄÁÙÊ±Öµ
unsigned int  Code_Data1 = 0; 		   //ºìÍâ½ÓÊÕ±àÂëµÄµÚÒ»×Ö½Ú
unsigned int  Code_Data2 = 0; 		 //ºìÍâ½ÓÊÕ±àÂëµÄµÚ¶þ¡¢Èý×Ö½Ú
unsigned char Code_Start_Flag = 0; //½ÓÊÕÊý¾Ý¿ªÊ¼±êÖ¾
unsigned char Data_Count =0; 
unsigned int  Blank_Count=0;
unsigned char Received_Buffer[Buffer_Size] = {0};   	//¶¨Òå½ÓÊÕ»º³åÇø 

unsigned char Receive_Data_Point = 0;        //¶¨Òå½ÓÊÕÊý¾Ý¸öÊýÖ¸Ê¾±äÁ¿ 
//unsigned char Com_End =0;       //
//unsigned char Receive_Data_Len = 0;		   //Êý¾Ý°ü³¤¶È

//unsigned char COMRecived_Complete_Flag = 0;	 //Êý¾Ý°ü½ÓÊÕÍê³É±êÖ¾



volatile unsigned int Timer2_Sec_Temp = 0;   //Timer2¼ÆÊý±äÁ¿
volatile unsigned int Sec_Count  = 0;	   //ÃëÖÓ¼ÆÊý


/*************************ÂÖÑ¯Ïà¹Ø±äÁ¿_START********************************/
unsigned char PRETPL_Count = 1;		//Ô¤°¸ÂÖÑ¯¼ÆÊý
unsigned int PRETPL_STime = 1;		//

/*************************ÂÖÑ¯Ïà¹Ø±äÁ¿_END********************************/

/*************************¹¦ÄÜÊý×é_START*********************************/

//unsigned char Temp[1]={0};		//ÁÙÊ±±äÁ¿
//unsigned char OutV[1]={0};
//unsigned char OutA[1]={0};
//unsigned char OutVGA[1]={0};

//unsigned char OutV_Tem[1]={0};
//unsigned char OutA_Tem[1]={0};
//unsigned char OutVGA_Tem[1]={0};

/************************¹¦ÄÜÊý×é_END************************************/

/**************************±¾ÎÄ¼þÄÚº¯ÊýÉêÃ÷_START************************************/
void State_Send(void);
void COM_LSend(unsigned char *Data,unsigned char Length);
void Stor_ADDR(unsigned char ADDR_Data);
void Save_PRE_Time(unsigned char Data_H,unsigned char Data_L,unsigned char PreNo);
void Save_Flag(unsigned char Data_Temp1);


/**************************±¾ÎÄ¼þÄÚº¯ÊýÉêÃ÷_END************************************/





void Port_Init(void)		//±ØÐë³õÊ¼»¯¶Ë¿Ú
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
	
	AUXR &= 0x7F;		//¶¨Ê±Æ÷Ê±ÖÓ12TÄ£Ê½
////	TMOD &= 0xF0;		//???????
	TMOD |= 0x02;		//ÉèÖÃ¶¨Ê±Æ÷ÎªÄ£Ê½2  8Î»×Ô¶¯ÖØ×°Ä£Ê½
	TL0 = 0xA4;		  //³õÖµ
	TH0 = 0xA4;		  //ÖØÔØÖµ
	TF0 = 0;		    //Çå³ýTF0±êÖ¾
	TR0 = 1;		    //¿ªÆô¶¨Ê±Æ÷0
	PT0 = 1;				//TimerÖÐ¶ÏµÄÓÅÏÈ¼¶¸ß
	ET0 = 1;  			//ÔÊÐíTime0ÖÐ¶Ï	
	
//	T2H = 0xB8; 			//11.0592M Ë«±¶ËÙÊ±10Ms
//	T2L	= 0x00;				//	
//	AUXR |= 0x10;			//			Ïàµ±ÓÚ	TR2 = 1; 
//	IE2  |= 0x04; 		//			Ïàµ±ÓÚ	ET2 = 1; 
}

void IE_Init(void)
{
	
	EX0 = 0;			//  ¹Ø±ÕÍâ²¿ÖÐ¶Ï0
	IT1 = 1;
	EX1= 1;			//  ¿ªÍâ²¿ÖÐ¶Ï1	
	
}

void Timer0_Interrupt(void) interrupt 1   //using 1 	   //¶¨Ê±Æ÷0ÖÐ¶Ï
{
	T_Temp++;			       //¶¨Òå¼ÆÊýÖÜÆÚÁÙÊ±±äÁ¿
	Blank_Count++;
	if(T_Temp > 2200)	    /// 2160
	{
		TR0 = 0;			//¹Ø±Õ¶¨Ê±Æ÷0
		T_Temp = 0;
		Data_Count = 0;
		Code_Data = 0;
		Code_Data2 = 0;
		Code_Start_Flag = 0;
		Blank_Count = 0;
	}
}


void External_Interrupt(void) interrupt 2 		//Íâ²¿ÖÐ¶Ï1  £¨ºìÍâÒ£¿Ø£©
{
	EX1 = 0;
	if(Code_Start_Flag)//ºìÍâ½ÓÊÕÊý¾Ý¿ªÊ¼
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
	else if(Blank_Count > 120 && Blank_Count < 150)//ºìÍâ¿ªÊ¼±êÖ¾
	{
		Code_Data = 0;
		Code_Data1 = 0;
		Code_Data2 = 0;
		Data_Count = 0;	
		Code_Start_Flag = 1;
		T_Temp = 0;	
	}
	else if(Data_Count == 0 && Code_Start_Flag == 0)//¶¨Ê±Æ÷¿ªÊ¼
	{
		TR0 = 1; 		
		T_Temp = 0;	
	}
	Blank_Count = 0;  

	EX1 = 1;	

}


//Timer2_interrupt(void) interrupt 12  // ¶¨Ê±Æ÷2ÖÐ¶Ï  (ÓÃÓÚÂÖÑ¯)
//{
//	Timer2_Sec_Temp++;
//	if(Timer2_Sec_Temp > 99)
//	{
//		Sec_Count++;
//		Timer2_Sec_Temp = 0;
//	}
//}


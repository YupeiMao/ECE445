#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <STC15F2K60S2.h>	//STC15W4K48S4 ר��ͷ�ļ�
#include <intrins.h>     //����_nop_()������ͷ�ļ�

/********************************���������ض���******************/
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

/***************************************************************/
// #define hx0801 1



/************************�������˿ڶ���_START*************************/

#define Beep_Port P63

/************************�������˿ڶ���_END***************************/

/************************����˿ڶ���_START***************************/

#define ICP_Port  P33

/***********************����˿ڶ���_END*****************************/


/**********************����оƬ���ƽӿڶ���_START*********************/ 

/*********************����оƬ���ƽӿڶ���_END************************/

/**********���̶˿ڶ���(����ʹ��74HC138 ����)_START*************************/

#define Key_V0  P01   //��74138 A0�˿� 
#define Key_V1  P10    //��74138 A1�˿� 
#define Key_V2  P12    //��74138 A2�˿� 
#define Key_V3  P14    //��74138 A2�˿� 

#define Key_H_All  P2   //ָʾ�ƶ˿�
#define Key_H0  P02 
#define Key_H1  P00
#define Key_H2  P11
#define Key_H3  P13
#define Key_H4  P13
#define Key_H5  P15
#define Key_H6  P16
#define Key_H7  P17

/********************���̶˿ڶ���(����ʹ��74HC138 ����)_END******************************/



/*****************************************************************************************
*  �������ã�����Բ�ͬ�Ļ�������Ӧ�޸ģ�
*  �������ã�����Բ�ͬ�Ļ�������Ӧ�޸ģ�
*  �������ã�����Բ�ͬ�Ļ�������Ӧ�޸ģ�
*****************************************************************************************/


/****************************��������_START**********************************************/ 
/****************************��������_START**********************************************/ 
/****************************��������_START**********************************************/ 

#define Present_Count 32			//Ԥ���������
#define TPL_Maxtime 30				//��ѯ���ʱ�䣨���ӣ�
#define LCD_Time 10	                 //��������ʱ��

#define ADDR0 0x2A          			  //�����豸�����൱�ڵ�ַ��
#define Buffer_Size 38              // ������ջ�������С


/**********************eeprom�洢��ַ����_START***********************/

#define VGA_Addr  0    			      //VGA�����ַ 
#define Video_Addr  VGA_Addr+32 		      //V�����ַ 
#define Audio_Addr Video_Addr+32    	      //A�����ַ
#define Function_Addr Audio_Addr+32         //���������ַ(���ܣ���ַ������) 

///����ֵ�洢����///
/// 0 | 1  |     2   |      3  	 |    4     |   5,6  |  7  	  |	  8   |   9  |   10 	|	11		|/////  
// Fun|ADDR|Baut_Rate|LCDS_Enable|TPL_Enable|TPL_Time|Lock_Key|Lock_IR|Ini_ed|PRETPL_ENB|Sound_ENB	|
                              
#define TPL_Fun_Addr Function_Addr+32    	  //��ѯ�洢��ַ
#define TPL_Addr TPL_Fun_Addr+32    	      //��ѯ�洢��ַ
#define PRETPL_Time_Addr TPL_Addr+32    	  //Ԥ����ѯʱ��洢��ʼ
#define Preset_Addr PRETPL_Time_Addr+64   	                  //Ԥ���洢��ַ��ʼ  


/***********************eeprom�洢��ַ����_END*****************************/


/****************************��������_END**********************************************/ 
/****************************��������_END**********************************************/ 
/****************************��������_END**********************************************/ 

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
extern unsigned char flag_press_ok;//�����
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
/********************ȫ�ֱ�������(������config.c�ļ���)����START*************************/
extern unsigned char Sound_ENB;        //��������������
extern unsigned int LCD_Sec;
extern unsigned int Sec_Count;	   //���Ӽ���

//extern unsigned char System_Init_Flag;

extern unsigned char Lock_Key;	            //�����̱�־λ 0��ʾû��
extern unsigned char Lock_IR;	               //��ң������־λ 0��ʾû��
extern unsigned char Lock_Device;	           //�����豸
extern unsigned char ID_Pressed;	           //ң����ID�����±�־

//extern unsigned char ADDR_Temp;
extern unsigned char idata Page;
//extern unsigned char Comdelay;

extern unsigned int T_Temp;					 //�������������ʱ����
//extern unsigned  char Count;
extern unsigned int Code_Data; 	     //������ձ������ʱֵ
extern unsigned int Code_Data1; 		 //������ձ���ĵ�һ�ֽ�
extern unsigned int Code_Data2; 		 //������ձ���ĵڶ������ֽ�
extern unsigned char Data_Count; 
extern unsigned int Blank_Count;
extern unsigned char Code_Start_Flag;	 //�������ݿ�ʼ��־


//extern unsigned char Fun_Ini;            //(���ܳ�ʼ��)��ֲ��Ҫ�޸�****
extern unsigned char Switch_Function;		   // Function of switching

#define DEFINE_LCD_SAVER_TIME 12000
extern unsigned char LCDS_Enable;	                  //����ʹ��
extern unsigned int  lcd_saver_time;

//extern unsigned char Device_Status;
extern unsigned char Baut_Rate;                //������ѡ��
extern unsigned char Baut_Rate_Q;                //������ѡ��

extern unsigned char Device_ID;

extern unsigned char Receive_Data_Point;       //����������ݸ���ָʾ���� 
//extern unsigned char Com_End;            	   //
//extern unsigned char COMRecived_Complete_Flag;	 //���ݰ�������ɱ�־
//extern unsigned char Receive_Data_Len;		   //���ݰ�����

extern unsigned char Out_Count;	    	//�������
extern unsigned char In_Count;				//��������
extern unsigned char InOut_Buf[];
extern unsigned char InOut_Buf_R[];

extern unsigned char Received_Buffer[];   			 //������ջ����� 
      


/*************************��ѯ��ر���********************************/
extern unsigned char PRETPL_Count;		//Ԥ����ѯ����
extern unsigned int PRETPL_STime;		//


//extern unsigned char Temp[];		//��ʱ����
//extern unsigned char OutV[];
//extern unsigned char OutA[];
//extern unsigned char OutVGA[];

//extern unsigned char OutV_Tem[];
//extern unsigned char OutA_Tem[];
//extern unsigned char OutVGA_Tem[];

/********************ȫ�ֱ�������(������config.c�ļ���)_END*************************/



/******************************����Ӳ��������������_START***************************/
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





/******************************����Ӳ��������������_END*****************************/

#endif




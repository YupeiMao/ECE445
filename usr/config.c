/****************************************************************
*Function:	��ʼ���Լ����������豸�����ڡ���ʱ�����ⲿ�жϣ��˿ڳ�ʼ��
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
#include "STC15F2K60S2.h"	//STC15W4K48S4 ר��ͷ�ļ�


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
/***********************************��ֲʱ��Ҫ�޸ĵ�����**************************/
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
/****************************��������_START**********************************************/ 
//unsigned char Fun_Ini = 0x07;            //(���ܳ�ʼ��)��ֲ��Ҫ�޸�****	  0x1A;  // û��
unsigned char Switch_Function = 0x07;	  	// Function of switching              �//�//û��

//unsigned char Device_Status=0;
unsigned char Baut_Rate = 3;    //������ѡ��  9600
unsigned char Baut_Rate_Q = 3;    //������ѡ��  9600

unsigned char Device_ID = 0;//
unsigned char Sound_ENB = 1;        //��������������
unsigned char LCDS_Enable = 0;	//����ʹ��
unsigned int lcd_saver_time = 0;

// #if hx0808
unsigned char Out_Count = 99;	  //�������
unsigned char In_Count = 99;			//��������
unsigned char InOut_Buf[100] = {0};
unsigned char InOut_Buf_R[100] = {0};

/********************ȫ�ֱ�������*************************/
unsigned char Lock_Key = 0;       //�����̱�־λ 0��ʾû��
unsigned char Lock_IR = 0;	     //��ң������־λ 0��ʾû��
unsigned char Lock_Device = 0;	 //�����豸
unsigned char ID_Pressed = 0;	    //ң����ID�����±�־

//unsigned char ADDR_Temp = 0;
unsigned char idata Page = 0;
//unsigned char Comdelay = 1;

unsigned int  T_Temp=0;				 //�������������ʱZ����
//unsigned char Count = 0;
unsigned int  Code_Data = 0; 	     //������ձ������ʱֵ
unsigned int  Code_Data1 = 0; 		   //������ձ���ĵ�һ�ֽ�
unsigned int  Code_Data2 = 0; 		 //������ձ���ĵڶ������ֽ�
unsigned char Code_Start_Flag = 0; //�������ݿ�ʼ��־
unsigned char Data_Count =0; 
unsigned int  Blank_Count=0;
unsigned char Received_Buffer[Buffer_Size] = {0};   	//������ջ����� 

unsigned char Receive_Data_Point = 0;        //����������ݸ���ָʾ���� 
//unsigned char Com_End =0;       //
//unsigned char Receive_Data_Len = 0;		   //���ݰ�����

//unsigned char COMRecived_Complete_Flag = 0;	 //���ݰ�������ɱ�־



volatile unsigned int Timer2_Sec_Temp = 0;   //Timer2��������
volatile unsigned int Sec_Count  = 0;	   //���Ӽ���


/*************************��ѯ��ر���_START********************************/
unsigned char PRETPL_Count = 1;		//Ԥ����ѯ����
unsigned int PRETPL_STime = 1;		//

/*************************��ѯ��ر���_END********************************/

/*************************��������_START*********************************/

//unsigned char Temp[1]={0};		//��ʱ����
//unsigned char OutV[1]={0};
//unsigned char OutA[1]={0};
//unsigned char OutVGA[1]={0};

//unsigned char OutV_Tem[1]={0};
//unsigned char OutA_Tem[1]={0};
//unsigned char OutVGA_Tem[1]={0};

/************************��������_END************************************/

/**************************���ļ��ں�������_START************************************/
void State_Send(void);
void COM_LSend(unsigned char *Data,unsigned char Length);
void Stor_ADDR(unsigned char ADDR_Data);
void Save_PRE_Time(unsigned char Data_H,unsigned char Data_L,unsigned char PreNo);
void Save_Flag(unsigned char Data_Temp1);


/**************************���ļ��ں�������_END************************************/





void Port_Init(void)		//�����ʼ���˿�
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
	
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
////	TMOD &= 0xF0;		//???????
	TMOD |= 0x02;		//���ö�ʱ��Ϊģʽ2  8λ�Զ���װģʽ
	TL0 = 0xA4;		  //��ֵ
	TH0 = 0xA4;		  //����ֵ
	TF0 = 0;		    //���TF0��־
	TR0 = 1;		    //������ʱ��0
	PT0 = 1;				//Timer�жϵ����ȼ���
	ET0 = 1;  			//����Time0�ж�	
	
//	T2H = 0xB8; 			//11.0592M ˫����ʱ10Ms
//	T2L	= 0x00;				//	
//	AUXR |= 0x10;			//			�൱��	TR2 = 1; 
//	IE2  |= 0x04; 		//			�൱��	ET2 = 1; 
}

void IE_Init(void)
{
	
	EX0 = 0;			//  �ر��ⲿ�ж�0
	IT1 = 1;
	EX1= 1;			//  ���ⲿ�ж�1	
	
}

void Timer0_Interrupt(void) interrupt 1   //using 1 	   //��ʱ��0�ж�
{
	T_Temp++;			       //�������������ʱ����
	Blank_Count++;
	if(T_Temp > 2200)	    /// 2160
	{
		TR0 = 0;			//�رն�ʱ��0
		T_Temp = 0;
		Data_Count = 0;
		Code_Data = 0;
		Code_Data2 = 0;
		Code_Start_Flag = 0;
		Blank_Count = 0;
	}
}


void External_Interrupt(void) interrupt 2 		//�ⲿ�ж�1  ������ң�أ�
{
	EX1 = 0;
	if(Code_Start_Flag)//����������ݿ�ʼ
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
	else if(Blank_Count > 120 && Blank_Count < 150)//���⿪ʼ��־
	{
		Code_Data = 0;
		Code_Data1 = 0;
		Code_Data2 = 0;
		Data_Count = 0;	
		Code_Start_Flag = 1;
		T_Temp = 0;	
	}
	else if(Data_Count == 0 && Code_Start_Flag == 0)//��ʱ����ʼ
	{
		TR0 = 1; 		
		T_Temp = 0;	
	}
	Blank_Count = 0;  

	EX1 = 1;	

}


//Timer2_interrupt(void) interrupt 12  // ��ʱ��2�ж�  (������ѯ)
//{
//	Timer2_Sec_Temp++;
//	if(Timer2_Sec_Temp > 99)
//	{
//		Sec_Count++;
//		Timer2_Sec_Temp = 0;
//	}
//}


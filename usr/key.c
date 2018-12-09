/****************************************************************
*Function:	���𰴼�ɨ�����ذ���������
*Author:	Valerian
*Date:		2012/4/13
*Version:	1.0
*
****************************************************************/

#include "key.h"
#include "config.h"
#include "code.h"
#include "beep.h"
#include "delay.h"
#include "led.h"
#include "eeprom.h"
#include "STC15F2K60S2.h"	//STC15W4K48S4 ר��ͷ�ļ�

void UART_Send_One(unsigned char Data);
unsigned char Turn_Check(void);
unsigned char key_scan(void);
/****************************************************************
*Function:	�����������룬��������ң��
*Input:		��������ֵ
*Output:	null
*Date:		2012/4/23
*
****************************************************************/
unsigned char key_left_val = 0xff;
unsigned char key_right_val = 0xff;

void  Analyse_Key(unsigned char key)  		
{
	unsigned char i = 0,CRC_Sum = 0,bian;
	unsigned char diao_dian = 0;
	static unsigned char flag_num_in_r = 0,flag_num_out_r = 0;
	static unsigned char flag_num_call_r = 0;
	

	static unsigned char flag_key_in_out_R;
	if(key == 0xff)
	{
		
	}
	else if(key != 0xff)
	{	
		if(flag_pos_set==0&&key==KEY_SAVE)
		{
			flag_key_in_out = SAVE;
			flag_pos_call_save = SAVE;
			
			flag_num_save = 0;
			Led_off_InOuCaSa();
			Led_Off_All();
			Led_On(KEY_SAVE);
			Func_Display_InOutCall(1);
		}
		else if(flag_pos_set==0&&key==KEY_CALL)
		{
			flag_key_in_out = CALL;
			flag_pos_call_save = CALL;
			flag_num_call = 0;
			Led_off_InOuCaSa();
			Led_Off_All();
			Led_On(KEY_CALL);
			Func_Display_InOutCall(1);
		}
		else if(flag_pos_set==0&&key==KEY_MENU)			
		{
//			flag_key_in_out = MENU;
			MENU_BIAOZI=1;
			flag_hold = MENU;
			Led_Off_All();
			Led_off_InOuCaSa();
			Led_On(KEY_MENU);
			
			flag_num_in_r = flag_num_in;
			flag_num_out_r = flag_num_out;
			flag_num_call_r = flag_num_call;
			
			flag_key_in_out_R = flag_key_in_out;


			if(flag_pos_set==0)
			{
				flag_pos_set = 1;						//����⵽menu�������µ�ʱ��flag_pos_set д������Ϊ 1
				flag_lcd_update = 1;
			}
		}
		else if(key==KEY_CTRL)
		{
			Led_Off_All();
			Led_On(KEY_MENU);
			Led_On(key);
			flag_hold = CTRL;
			if(flag_pos_set)
			{
				Func_Display_MenuCal(key);
			}
			if(flag_pos_set==0)
			{
				if(N_Fanye==1)
				{
					N_Fanye = 0;
				}
				else 
					Fan_Ye();
			}
			else if(flag_pos_set==132)
			{
				z++;
			}
		}
		else if(key==KEY_ESC)
		{
			Led_Off_All();
			Led_On(KEY_MENU);
			Led_On(KEY_ESC);
			if((flag_pos_set==132)&&(bian==1))
			{				
				Func_Display_Desk();		//��Ҫ�޸�
				flag_pos_set=0;
				bian=0;
      }
			else if(flag_pos_set)
			{
				flag_pos_set = flag_pos_set/10;
				if(flag_pos_set == 0)
				{	
					Func_Display_Desk();	//��Ҫ�޸�
				}
				flag_lcd_update = 1;
			}
			if((flag_pos_set == 1)||(flag_pos_set == 132))
			{
				flag_hold = 0;
			}
		}
		else if(key==KEY_OK)
		{
			Led_Off_All();
			Led_On(KEY_MENU);			
			Led_On(KEY_OK);
			if(flag_pos_set)
			{
				Func_Display_MenuCal(key);
			}
			else
			{
				if(flag_key_in_out == SAVE)
				{  
					MENU_BIAOZI=0; 
					bian=1;	
			    flag_pos_set=132;
										
					flag_lcd_update=1;
				  Func_Display_Menu();
				}
				else if(flag_key_in_out == CALL)
				{
					Func_Load_pre(flag_num_call);
				}
				else if(Out_Count<10)
				{
					if(flag_num_out)
						{
							Switch_Next(flag_num_in,flag_num_out);
						}
           else
						{
							all_switch = 1;
							Switch_All_Next();//����ϵ��okȻ��ҳ��flag_num_out��ֵ������0���Ͱ�����ͨ������Ϊ�㣬����Ҫ���籣��
							
							cleaing_in=1;//����ң�ذ������ٰ��������ܹ�ʹ���ִ��¸�ֵ
				  		cleaing_out=1;
						} 
        }
				else if(Out_Count>9)
				{
						if(flag_num_out)
						{
							Switch_Next(flag_num_in,flag_num_out);
						}
						else
						{
							all_switch = 1;
							Switch_All_Next();//����ϵ��okȻ��ҳ��flag_num_out��ֵ������0���Ͱ�����ͨ������Ϊ�㣬����Ҫ���籣��
						} 
						cleaing_in=1;//����ң�ذ������ٰ��������ܹ�ʹ���ִ��¸�ֵ
						cleaing_out=1;
				}
			}
			flag_ok = 1;
			flag_key_in_out_R = flag_key_in_out;
//			flag_num_save_r = flag_num_save;
			flag_hold = OK;
			flag_press_ok = OK;
		}
		
		else if(flag_pos_set==0&&key==KEY_IN)
		{
			flag_key_in_out = IN;
			flag_num_in=0;
			Led_off_InOuCaSa();
			Led_Off_All();
			Led_On(KEY_IN);
		}
		else if(flag_pos_set==0&&key==KEY_OUT)
		{
			flag_key_in_out = OUT;
			all_switch = 0;
			
			flag_num_out=0;
			Led_off_InOuCaSa();
			Led_Off_All();
			Led_On(KEY_OUT);
		} 
		else if(key==KEY_AV)
		{
			key=0;
      Switch_Yuan('[');
    }
		else if(key==KEY_VGA)
		{
			key=0;
      Switch_Yuan(']');
    }
		else if(key==KEY_A)
		{
 			key=0;
      Switch_Yuan('{');
    }
		else if(key==KEY_V)
		{
			key=0;
      Switch_Yuan('}');
    }
		 else if((key>=KEY_1&&key<=KEY_0)||(key==KEY_ALL))/////ԭ����else if
		{

			if(IR_BIAOZI==1)//Ϊ��ʵ�ֺ������������Ĳ����Ĳ�ͬ�����������������
			  {
						IR_BIAOZI=0;
						Led_On(key);
					  if((flag_key_in_out != CALL)&&(flag_key_in_out != SAVE))
				   {
						 if(cleaing_out==1)
							{
								cleaing_out=0;
								flag_num_out=0;
							}
							 
			  		if(key>=KEY_1&&key<=KEY_9)flag_num_out = flag_num_out*10+key;
						else if(key==KEY_0)
						{
							if(flag_num_out)
							flag_num_out = flag_num_out*10+0;
							else
							{
//                Fan_Ye();     
              }
						}
						else if(key==KEY_ALL)
							{
								Switch_All_Next();
								flag_num_out = 0;
								cleaing_out=1;
								cleaing_in=1;
								return;
							}
							if(flag_num_out>Out_Count)
							{
								flag_num_out = Out_Count;
							}
							
							I2CBus_WriteFromBuf(OUT_NUM,&flag_num_out,1);/////////////////////////////
							
							if(flag_num_out>9)
							{
									Switch_Next(flag_num_in,flag_num_out);
								  cleaing_in=1;//����ң�ذ������ٰ��������ܹ�ʹ���ִ��¸�ֵ
									cleaing_out=1;
              }
							if(flag_num_out<10)
							{
								 if(flag_num_out)
								{
									Switch_Next(flag_num_in,flag_num_out);
									cleaing_in=1;//����ң�ذ������ٰ��������ܹ�ʹ���ִ��¸�ֵ
									cleaing_out=1;
								}
							}								
				    }
						
						if(flag_pos_set)
						{
								Func_Display_MenuCal(key);
						}
		   	}       
			else
				{
					Led_Off_All();
					Led_On(KEY_MENU);
					Led_off_InOuCaSa();
					Led_On(key);
			
				
				if(flag_pos_set==0)
				{
				
					if(flag_key_in_out == OUT)
					{
						if(	flag_ok == 1)
						{
							all_switch = 0;//
							flag_num_out = 0;
							flag_ok = 0;
						}
						if(key>=KEY_1&&key<=KEY_9)flag_num_out = flag_num_out*10+key;
						else if(key==KEY_0)flag_num_out = flag_num_out*10+0;
						if(flag_num_out>Out_Count)flag_num_out = Out_Count;
						Led_On(KEY_OUT);

						I2CBus_WriteFromBuf(OUT_NUM,&flag_num_out,1);/////////////////////////////
						
						if(flag_num_out>9)
						{
         				Switch_Next(flag_num_in,flag_num_out);
            }
						if(flag_num_out<10)
						{
							if(flag_num_out < Out_Count)
							{
								
								if(flag_num_out>Out_Count)flag_num_out = Out_Count;
								
//								if(flag_num_out)
//							{
//								Switch_Next(flag_num_in,flag_num_out);
								cleaing_in=1;//����ң�ذ������ٰ��������ܹ�ʹ���ִ��¸�ֵ
					    	cleaing_out=1;
//								flag_key_in_out=OK;
//							}															
							}
//							Switch_Next(flag_num_in,flag_num_out);
//							flag_key_in_out = OK;
						}
					}
					else if(flag_key_in_out == IN)
					{
						if(	flag_ok == 1)
						{
							flag_num_in = 0;
							flag_ok = 0;
						}
						if(key>=KEY_1&&key<=KEY_9)flag_num_in = flag_num_in*10+key;
						else if(key==KEY_0)flag_num_in = flag_num_in*10+0;
						if(flag_num_in>In_Count)flag_num_in= In_Count;
						Led_On(KEY_IN);
						
					  I2CBus_WriteFromBuf(IN_NUM,&flag_num_in,1);//////////////////////
						
//						if(Out_Count==1)
//						{
//							Switch_Next(flag_num_in,Out_Count);
//						}
					}
					else if(flag_key_in_out == CALL)
					{
						if(	flag_ok == 1)
						{
							flag_num_call = 0;
							flag_ok = 0;
						}
						if(key>=KEY_1&&key<=KEY_9)flag_num_call = flag_num_call*10+key;
						else if(key==KEY_0)
						{ 
							if(flag_num_call)
							flag_num_call = flag_num_call*10+0;
							else
							{
//                Fan_Ye();
              }
						}
						if(flag_num_call>32)flag_num_call= 32;
						Led_On(KEY_CALL);
					}
					
					
					else if(flag_key_in_out == SAVE)
					{
						if(	flag_ok == 1)
						{
							flag_num_save = 0;
							flag_ok = 0;
						}
						if(key>=KEY_1&&key<=KEY_9)flag_num_save = flag_num_save*10+key;
							else if(key==KEY_0)
							{
								if(flag_num_save)
								flag_num_save = flag_num_save*10+0;
								else
								{
//									Fan_Ye();
								}
							}
							if(flag_num_save>32)flag_num_save= 32;
							Led_On(KEY_SAVE);					
					}
				}
				
				if(flag_pos_set==132)
				{
					
					if((z%2)==0)
					{
						if(key>=KEY_1&&key<=KEY_9)flag_num_save = flag_num_save*10+key;
							else if(key==KEY_0)
							{
								if(flag_num_save)
								flag_num_save = flag_num_save*10+0;
								else
								{
//									Fan_Ye();
								}
							}
							if(flag_num_save>32)flag_num_save= 32;
					}
					else			//��������
					{
					
					}
				}
				if(flag_pos_set==0)
				{
							if(key==KEY_0) //�� 0 ��ҳ 
						 {
//								Fan_Ye();
						 }
					 
				}
					
					if(flag_pos_set)
					{
						Func_Display_MenuCal(key);
					}
	  	}
	}
		////////////
		else if(key>=KEY_1_i&&key<=KEY_0_i)
		{
			if(cleaing_in==1)
			{
				cleaing_in=0;
				flag_num_in=0;
			}
// 				flag_key_in_out=OK;//����ͨ����ң�ذ������10+���ٰ�0���Է�ҳ�����ǰ������������־�ֱ�ӽ���λok���˳���ҳ
		if(key>=KEY_1_i&&key<=KEY_5_i)flag_num_in = flag_num_in*10+key-0x81;
		else if(key>=KEY_6_i&&key<=KEY_9_i)flag_num_in = flag_num_in*10+key-0x82;
		else if(key==KEY_0_i)flag_num_in = flag_num_in*10+0;
		if(flag_num_in>In_Count)flag_num_in= In_Count;
		I2CBus_WriteFromBuf(IN_NUM,&flag_num_in,1);/////////////////////////////

		if(Out_Count==1)
		{
			Switch_Next(flag_num_in,Out_Count);
			cleaing_in=1;
			cleaing_out=1;
		}
	 }			 
	 
		if(flag_pos_set==0)
		{
			switch_disp = 1;
			Led_off_menu();
			if(flag_key_in_out == IN )
			{
					Led_On(KEY_IN);
			}
			else if(flag_key_in_out == OUT )
			{
					Led_On(KEY_OUT);
			}
			else if(flag_key_in_out == CALL )
			{
					Led_On(KEY_CALL);
			}
			else if(flag_key_in_out == SAVE )
			{
					Led_On(KEY_SAVE);
			}
		}
		
		if(flag_hold == 0)
		{
			flag_num_in = flag_num_in_r;
			flag_num_out = flag_num_out_r;
			flag_num_call = flag_num_call_r;
//			flag_num_save = flag_num_save_r;
			flag_key_in_out = flag_key_in_out_R;
			flag_hold = 2;
		}
		
//		if((flag_pos_set==132)&&(key==KEY_CTRL))
//		{
//				z++;
//		}
		if(flag_pos_set==132)
		{
				if((flag_ok == 1)&&(flag_key_in_out == SAVE))
					{
						Led_off_menu();
						Led_On(KEY_SAVE);
					}
		}
//		if((flag_pos_set==0)&&(key==KEY_CTRL))
//		{
//			Fan_Ye();
//		}
	}
}


void Keyscan(void) 		// Scan the keyboard
{
	unsigned char a,b;
	static unsigned char a_r, b_r;  //��һ�ε�ֵ
	
	a = key_scan();
	b = Turn_Check();
	

	if(Lock_Key==1)
	{
		N_Fanye = 1;
 		if((a==KEY_CTRL)&&(b==KEY_0))
		{
			
			Lock_Key=0;
		  I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_LOCK_KEY,&Lock_Key,1);
    }
	}
		if((a==KEY_CTRL)&&(b==KEY_1))
		{
				N_Fanye = 1;
				Switch_Yuan('}');
		}
		else if((a==KEY_CTRL)&&(b==KEY_2))
		{
				N_Fanye = 1;
				Switch_Yuan('{');
		}
		else if((a==KEY_CTRL)&&(b==KEY_3))
		{
				N_Fanye = 1;
				Switch_Yuan(']');
		}

	if((a_r == a) && (b_r == b))
	return;
	a_r = a;
	b_r = b;
	
	if(a!=0xff)
	{
		SBeep();
		if(lcd_saver_time <= DEFINE_LCD_SAVER_TIME)
		{
			Analyse_Key(a);
		}
		lcd_saver_time = 0;
	}
	else if(b!=0xff)
	{
		SBeep();
		if(lcd_saver_time<=DEFINE_LCD_SAVER_TIME)
		{
			Analyse_Key(b);
		}
		lcd_saver_time = 0;
	}
	key_right_val = b;
	key_left_val = a;

}

#define key_delay_tim 10
//���ܼ�ɨ��
unsigned char key_scan(void)
{
	KEY_S1 = 1;KEY_S2 = 1;KEY_S3 = 1;KEY_S4 = 1;KEY_S5 = 1;KEY_S6 = 1;
	
		if(Lock_Key==1)   //��������
		{
			if(KEY_S2==0)
			{
				delay_ms(key_delay_tim);
				if(KEY_S2==0)
				return KEY_CTRL;
			}
			return 0xff;
		}
	
		if(KEY_S1==0)
		{
			delay_ms(key_delay_tim);
			if(KEY_S1==0)return KEY_ESC;
		}
		else if(KEY_S2==0)
		{
			delay_ms(key_delay_tim);
			if(KEY_S2==0)return KEY_CTRL;
		}
		else if(KEY_S3==0)
		{
			delay_ms(key_delay_tim);
			if(KEY_S3==0)return KEY_CALL;
		}
		else if(KEY_S4==0)
		{
			delay_ms(key_delay_tim);
			if(KEY_S4==0)return KEY_MENU;
		}
		else if(KEY_S5==0)
		{
			delay_ms(key_delay_tim);
			if(KEY_S5==0)return KEY_OK;
		}
		else if(KEY_S6==0)
		{
			delay_ms(key_delay_tim);
			if(KEY_S6==0)return KEY_SAVE;
		}
		return 0xff;
}


//���ּ�ɨ��

unsigned char Turn_Check(void)
{
	KEY_H1 = 0;KEY_H2 = 1;KEY_H3 = 1;
	KEY_L1 = 1;KEY_L2 = 1;KEY_L3 = 1;KEY_L4 = 1;
	if(Lock_Key==1)   //��������
	{
      KEY_H1 = 1;KEY_H2 = 1;KEY_H3 = 0;
    	KEY_L1 = 1;KEY_L2 = 1;KEY_L3 = 1;KEY_L4 = 1; 	
		if(KEY_L3==0)
		{	
			delay_ms(key_delay_tim);
			if(KEY_L3==0)return KEY_0;
		}
		return 0xff;
	}
	if(KEY_L1==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L1==0)return KEY_IN;
	}
	else if(KEY_L2==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L2==0)return KEY_1;
	}
	else if(KEY_L3==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L3==0)return KEY_2;
	}
	else if(KEY_L4==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L4==0)return KEY_3;
	}
	
	KEY_H1 = 1;KEY_H2 = 0;KEY_H3 = 1;
	KEY_L1 = 1;KEY_L2 = 1;KEY_L3 = 1;KEY_L4 = 1;
	if(KEY_L1==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L1==0)return KEY_4;
	}
	else if(KEY_L2==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L2==0)return KEY_5;
	}
	else if(KEY_L3==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L3==0)return KEY_6;
	}
	else if(KEY_L4==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L4==0)return KEY_7;
	}
	
	KEY_H1 = 1;KEY_H2 = 1;KEY_H3 = 0;
	KEY_L1 = 1;KEY_L2 = 1;KEY_L3 = 1;KEY_L4 = 1;
	if(KEY_L1==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L1==0)return KEY_8;
	}
	else if(KEY_L2==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L2==0)return KEY_9;
	}
	else if(KEY_L3==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L3==0)return KEY_0;
	}
	else if(KEY_L4==0)
	{
		delay_ms(key_delay_tim);
		if(KEY_L4==0)return KEY_OUT;
	}
	
	P0 = 0xFF;
	return 	0xff;
}

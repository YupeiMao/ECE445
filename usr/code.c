#include "code.h"
#include "2402.h"
#include "config.h"
#include "delay.h"
#include "key.h"
#include "uart.h"
#include "eeprom.h"
#include "led.h"
/***********定义设备型号（可改变）***************/
unsigned char tab;

unsigned char Xinghao[24]=  {"         HX0808         "};//设备类型“XW-VG0404” 讯维
unsigned char Xinghao1[24]= {"     Matrix switch      "};// 设备品牌Matrix Switch 字符

//unsigned char Xinghao[24]=  {"                        "};//设备类型“XW-VG0404” 讯维
//unsigned char Xinghao1[24]= {"                        "};// 设备品牌Matrix Switch 字符


unsigned char code Display_Str[9]={"x12345678"};

sbit Lcd_Light    =   P6^4;

void Switch_Yuan( unsigned char yuan)
{
	unsigned char buf[16];
	unsigned int i= 0;
	buf[i++] = '*';
	buf[i++] = '@';                  
	buf[i++] = yuan;
	buf[i++] = '!';
	UART_Send(buf ,i);
}

void GetID_send()
{
	unsigned char buf1[3];
		buf1[0] = '*';
		buf1[1] = '0';
		buf1[2] = '!';
		UART_Send(buf1 ,3);
}
void Get_xinghao()
{
	unsigned char buf1[3];
	if(get_xinh == 0) 
	{
		delay_ms(80);
		buf1[0] = '*';
		buf1[1] = '$';
		buf1[2] = '!';
		UART_Send(buf1 ,3);
	}
}
void IOpress_disp()
{
				unsigned char buf[2];
		
				buf[0] = flag_num_in/10+'0';
				buf[1] = flag_num_in%10+'0';
				Lcd_Display(1,3,buf,2);
				buf[0] = ' ';
				Lcd_Display(1,5,buf,1);
			
			  buf[0] = flag_num_out/10+'0';
				buf[1] = flag_num_out%10+'0';
				Lcd_Display(2,3,buf,2);
				buf[0] = ' ';
				Lcd_Display(2,5,buf,1);
			
				buf[0] = flag_num_save/10+'0';
				buf[1] = flag_num_save%10+'0';
				Lcd_Display(2,23,buf,2);
			
				buf[0] = flag_num_call/10+'0';
				buf[1] = flag_num_call%10+'0';
				Lcd_Display(2,23,buf,2);


		if(flag_key_in_out == IN)
		{
			if(flag_num_in==0)
			{
				buf[0] = flag_num_in + '0';
				buf[1] = '_';
				Lcd_Display(1,3,buf,2);
				buf[0] = ' ';
				Lcd_Display(1,5,buf,1);
			}
			else if((flag_num_in<10)&&(flag_num_in>0))
			{
				buf[0] = '0';
				buf[1] = flag_num_in + '0';
				Lcd_Display(1,3,buf,2);
				buf[0] = '_';
				Lcd_Display(1,5,buf,1);
			}
			else if((flag_num_in>=10)&&(flag_num_in<100))
			{
				buf[0] = flag_num_in/10+'0';
				buf[1] = flag_num_in%10+'0';
				Lcd_Display(1,3,buf,2);
				buf[0] = '_';
				Lcd_Display(1,5,buf,1);
			}
		}
		else if(flag_key_in_out == OUT)
		{
			if(flag_num_out==0)
			{
				buf[0] = flag_num_out + '0';
				buf[1] = '_';
				Lcd_Display(2,3,buf,2);		
				buf[0] = ' ';
				Lcd_Display(1,5,buf,1);
			}
			else if((flag_num_out<10)&&(flag_num_out>0))
			{
				buf[0] = '0';
				buf[1] = flag_num_out + '0';
				Lcd_Display(2,3,buf,2);
				buf[0] = '_';
				Lcd_Display(2,5,buf,1);

			}
			else if((flag_num_out<100)&&(flag_num_out>=10))
			{
				buf[0] = flag_num_out/10+'0';
				buf[1] = flag_num_out%10+'0';
				Lcd_Display(2,3,buf,2);
				buf[0] = '_';
				Lcd_Display(2,5,buf,1);
			}
			
			if(all_switch == 1)
			{
				buf[0] = 'A';
				buf[1] = 'L';
				Lcd_Display(2,3,buf,2);
				buf[0] = '_';
				Lcd_Display(2,5,buf,1);
			}	
		}
		else if(flag_key_in_out == CALL)
		{
			if(flag_num_call==0)
			{
				buf[0] = flag_num_call + '0';
				buf[1] = '_';
				Lcd_Display(2,23,buf,2);		
			}
			else if((flag_num_call<10)&&(flag_num_call>0))
			{
				buf[0] = '0';
				buf[1] = flag_num_call + '0';
				Lcd_Display(2,23,buf,2);
//				buf[0] = '_';
//				Lcd_Display(2,24,buf,1);
			}
			else if((flag_num_call<33)&&(flag_num_call>=10))
			{
				buf[0] = flag_num_call/10+'0';
				buf[1] = flag_num_call%10+'0';
				Lcd_Display(2,23,buf,2);
//				buf[1] = '_';
//				Lcd_Display(2,24,buf,1);
			}
		}
		else if(flag_key_in_out == SAVE)
		{
			if(flag_num_save ==0)
			{
				buf[0] = flag_num_save + '0';
				buf[1] = '_';
				Lcd_Display(2,23,buf,2);		
			}
			else if((flag_num_save<10)&&(flag_num_save>0))
			{
				buf[0] = '0';
				buf[1] = flag_num_save + '0';
				Lcd_Display(2,23,buf,2);
//				buf[0] = '_';
//				Lcd_Display(2,24,buf,1);

			}
			else if((flag_num_save<33)&&(flag_num_save>=10))
			{
				buf[0] = flag_num_save/10+'0';
				buf[1] = flag_num_save%10+'0';
				Lcd_Display(2,23,buf,2);
//				buf[1] = '_';
//				Lcd_Display(2,24,buf,1);
			}
		}
		else if(flag_press_ok == OK)
		{
			buf[0] = flag_num_in/10 + '0';
			buf[1] = flag_num_in%10 + '0';
			Lcd_Display(1,3,buf,2);
			buf[0]= ' ';
			Lcd_Display(1,5,buf,1);
			buf[0] = flag_num_out/10 + '0';
			buf[1] = flag_num_out%10 + '0';
			Lcd_Display(2,3,buf,2);
			buf[0]= ' ';
			Lcd_Display(2,5,buf,1);
			flag_press_ok = 0;		
		}
		
	
}

unsigned char Func_Crc_Sum(unsigned char *pDat,unsigned char pLen)
{
	unsigned char sum = 0,i;
	for(i=0;i<pLen;i++)
	{
		sum = sum + pDat[i];
	}
	return sum;
}

void Switch_Next(unsigned char Input_Num, unsigned char Output_Num)
{
	unsigned char buf[16];
	unsigned int i= 0;
	buf[i++] = 0x2a;
	buf[i++] = Output_Num/10%10+'0';
	buf[i++] = Output_Num%10+'0';
	buf[i++] = '<'; 
	buf[i++] = Input_Num/10%10+'0';
	buf[i++] = Input_Num%10+'0';
	buf[i++] = '!';
	UART_Send(buf ,i);
}

void Switch_All_Next(void)
{
	unsigned char buf[16];
	unsigned int i= 0;
	buf[i++] = 0x2a;
	buf[i++] = 'I';
	buf[i++] = flag_num_in/10%10+'0';
	buf[i++] = flag_num_in%10+'0';
	buf[i++] = 'O';
	buf[i++] = 'A';
	buf[i++] = 'L';
	buf[i++] = '<';
	buf[i++] = '!';
	UART_Send(buf ,i);
}

void Switch_Update(void)
{
	unsigned char buf[16];
	unsigned char i= 0;
	buf[i++] = 0x2a;
	buf[i++] = '!';
	UART_Send(buf ,i);
}
void Switch_Modify_DeviceID(unsigned char id)
{
	unsigned char buf[16];
	unsigned char i= 0;
	if((id/10)==0)buf[i++] = '*';
	else buf[i++] = id/10-1+'A';
	if(id%10)buf[i++] = id%10-1+'A';
	else buf[i++] = 'A';
	buf[i++] = '!';
	UART_Send(buf ,i);
}

void Switch_Modify_BaudRate(unsigned char br)
{
	unsigned char buf[16];
	unsigned char i= 0;
	buf[i++] = '*';
	buf[i++] = 'S';
	if(br>=1&&br<=3)buf[i++] = br+'0';
	else buf[i++] = '3';
	buf[i++] = Func_Crc_Sum(buf,3);
	buf[i++] = '!';
	UART_Send(buf ,i);
}
void Switch_Modify_SystemInitialize(void)
{
	unsigned char buf[16];
	unsigned char i= 0;
	buf[i++] = '*';
	buf[i++] = 'E';
	buf[i++] = '0';
	buf[i++] = Func_Crc_Sum(buf,3);
	buf[i++] = '!';
	UART_Send(buf ,i);
}




void Func_Init_Sound(void)
{
	I2CBus_ReadToBuf(DEFINE_EEP_ADDR_SOUND,&Sound_ENB,1);
	if(Sound_ENB>1)
	{
		Sound_ENB = 1;
		I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_SOUND,&Sound_ENB,1);
	}
}
void Func_Modify_Sound(void)
{
	I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_SOUND,&Sound_ENB,1);
}
void Func_Init_LcdSaver(void)
{
	I2CBus_ReadToBuf(DEFINE_EEP_ADDR_LCDS,&LCDS_Enable,1);
	if(LCDS_Enable>1)
	{
		LCDS_Enable = 0;
		I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_LCDS,&LCDS_Enable,1);
	}
}
void Func_Modify_LcdSaver(void)
{
	I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_LCDS,&LCDS_Enable,1);
}
void Func_LcdSaver(void)
{
	if(LCDS_Enable)
	{
		if(lcd_saver_time>DEFINE_LCD_SAVER_TIME)
		{
			Lcd_Light = 1;
			Led_Off_All();
		}
		else
		{
			delay_ms(2);
			lcd_saver_time++;
			Lcd_Light = 0;
		}
	}
}
void Func_Pre_cmd(unsigned char cmd)
{
	unsigned char buff[6];
	buff[0] = '*';
	buff[1] = 0xff;
	buff[2] = 3;
	buff[3] = cmd;
	buff[4] = 0xff;
	buff[5] = '!';
	UART_Send(buff, 6);
}
void Func_Load_pre(unsigned char Num)
{
	unsigned char buff[6];
	buff[0] = '*';
	buff[1] = Num;
	buff[2] = 2;
	buff[3] = 0xff;
	buff[4] = 0xff;
	buff[5] = '!';
	
	UART_Send(buff, 6);
}
void Func_Save_pre(unsigned char Num, unsigned int Time)
{
	unsigned char buff[6];
	buff[0] = '*';
	buff[1] = Num;
	buff[2] = 1;
	buff[3] = (Time>>8);
	buff[4] = Time;
	buff[5] = '!';
	UART_Send(buff, 6);
}

void Func_Display_XingHao(void)	  //型号显示
{	
	if(flag_xinghao_update==1)
	{
	Lcd_Display(1,1,Xinghao1,24);//设备品牌Matrix Switch 字符
	Lcd_Display(2,1,Xinghao,24);
	a = 1;
	flag_xinghao_update = 0;
	switch_disp = 0;
	}
}

void Func_Display_InOutCall(unsigned char init)
{
////	unsigned char buf[2];
////	static unsigned char cnt = 0;
////	static unsigned char flag_num_in_r = 0,flag_num_out_r = 0;
////	static unsigned char flag_num_call_r = 0,flag_num_save_r = 0;
////	static unsigned char flag_pos_call_save_r = 0;
	
if(init)
{
////	cnt = 0;		
	if(flag_pos_call_save==SAVE)
	{
		Lcd_Display(1,1,"I:",2);

		Lcd_Display(1,21," SAV",4);

		Lcd_Display(2,1,"O:",2);

		Lcd_Display(2,21," :",2);
	}
	else 
	{
		flag_pos_call_save = CALL;
		Lcd_Display(1,1,"I:",2);
//		Lcd_Display(1,5," ",1);
		Lcd_Display(1,21," CAL",4);

		Lcd_Display(2,1,"O:",2);
//		Lcd_Display(2,5," ",1);
		Lcd_Display(2,21," :",2);
	}
}
//	if(key_left_val!=0xFF)return;
////	if(cnt<1)
////	{
////			buf[0] = flag_num_in/10 + '0';
////			buf[1] = flag_num_in%10 + '0';
////			Lcd_Display(1,3,buf,2);
////			
////			buf[0] = flag_num_out/10 + '0';
////			buf[1] = flag_num_out%10 + '0';
////			Lcd_Display(2,3,buf,2);

////		if(flag_pos_call_save==SAVE)
////		{
////			buf[0] = flag_num_save/10 + '0';
////			buf[1] = flag_num_save%10 + '0';
////		}
////		else
////		{
////			buf[0] = flag_num_call/10 + '0';
////			buf[1] = flag_num_call%10 + '0';
////		}
////		Lcd_Display(2,23,buf,2);
////		
////		cnt++;
////	}
////	else
////	{
////		if(flag_num_in_r!=flag_num_in || flag_num_out_r!=flag_num_out 
////	  ||flag_num_call_r!=flag_num_call || flag_num_save_r!=flag_num_save 
////		||flag_pos_call_save_r != flag_pos_call_save)
////		{
////			flag_num_in_r   = flag_num_in;
////			flag_num_out_r  = flag_num_out;
////			flag_num_call_r = flag_num_call;
////			flag_num_save_r = flag_num_save;
////			flag_pos_call_save_r = flag_pos_call_save;
//// 			cnt = 0;
////		}
////	}
}

void ddisplay	(unsigned char page1, unsigned char out_max)
{
			unsigned char buf1[2];
	    unsigned char temp;
		  unsigned char j;//函数里面定义的便便利每次进入函数是都会吧定义是的值付给他吗?
// 		if(out_num<out_max)  //  改变的路数在那个范围里面就显示那一页
// 	{ 
		  change_page=page1;
if(out_max<((page1+1)*4+1))
	{			
//				Start_Beep();
//				delay_ms(500);
//				Start_Beep();
		  switch(out_max%4)
		{ 
			case 1:
			Lcd_Display(1,6,"  00->         ",15);
			Lcd_Display(2,6,"               ",15);break;
			case 2:
			Lcd_Display(1,6,"  00->   00->  ",15);
			Lcd_Display(2,6,"               ",15);break;
			case 3:
			Lcd_Display(1,6,"  00->   00->  ",15);
			Lcd_Display(2,6,"  00->         ",15);break;
			case 0:
			Lcd_Display(1,6,"  00->   00->  ",15);
			Lcd_Display(2,6,"  00->   00->  ",15);break;
			default:
			break;
		}
		for(j=4*page1;j<(out_max%4)+4*page1;j++)
		{
			temp = InOut_Buf[j];
			buf1[0] = temp/10 + '0';
			buf1[1] = temp%10 + '0';
			if(j==4*page1)
			{Lcd_Display(1,8,buf1,2);}
		  else if(j==4*page1+1)
			{Lcd_Display(1,15,buf1,2);}
			else if(j==4*page1+2)
			{Lcd_Display(2,8,buf1,2);}
			else if(j==4*page1+3)
			{Lcd_Display(2,15,buf1,2);}
		}
		if(out_max%4==0)
		{
					for(j=4*page1;j<4*page1+4;j++)
				{
					temp = InOut_Buf[j];
					buf1[0] = temp/10 + '0';
					buf1[1] = temp%10 + '0';
					if(j==4*page1)
					{Lcd_Display(1,8,buf1,2);}
					else if(j==4*page1+1)
					{Lcd_Display(1,15,buf1,2);}
					else if(j==4*page1+2)
					{Lcd_Display(2,8,buf1,2);}
					else if(j==4*page1+3)
					{Lcd_Display(2,15,buf1,2);}
				} 
    }
		for(j=4*page1;j<(out_max%4)+4*page1;j++)
		{
			buf1[0]=(j+1)/10+'0';/////
			buf1[1]=(j+1)%10+'0';/////
			if(j==4*page1)
			{Lcd_Display(1,12,buf1,2);}
		  else if(j==4*page1+1)
			{Lcd_Display(1,19,buf1,2);}
			else if(j==4*page1+2)
			{Lcd_Display(2,12,buf1,2);}
			else if(j==4*page1+3)
			{Lcd_Display(2,19,buf1,2);}
		}
		if(out_max%4==0)
		{
				for(j=4*page1;j<4*page1+4;j++)
			{
				buf1[0]=(j+1)/10+'0';//////
				buf1[1]=(j+1)%10+'0';////////
				if(j==4*page1)
				{Lcd_Display(1,12,buf1,2);}
				else if(j==4*page1+1)
				{Lcd_Display(1,19,buf1,2);}
				else if(j==4*page1+2)
				{Lcd_Display(2,12,buf1,2);}
				else if(j==4*page1+3)
				{Lcd_Display(2,19,buf1,2);}
			} 
    }
	}
	else
		{
		Lcd_Display(1,6,"  00->   00->  ",15);
		Lcd_Display(2,6,"  00->   00->  ",15);
			for(j=4*page1;j<4*page1+4;j++)
				{
					temp = InOut_Buf[j];
					buf1[0] = temp/10 + '0';
					buf1[1] = temp%10 + '0';
					if(j==4*page1)
					{Lcd_Display(1,8,buf1,2);}
					else if(j==4*page1+1)
					{Lcd_Display(1,15,buf1,2);}
					else if(j==4*page1+2)
					{Lcd_Display(2,8,buf1,2);}
					else if(j==4*page1+3)
					{Lcd_Display(2,15,buf1,2);}
				} 
		for(j=4*page1;j<4*page1+4;j++)
				{
					buf1[0]=(j+1)/10+'0';/////////////////////////////////////////////////////
					buf1[1]=(j+1)%10+'0';//////
					if(j==4*page1)
					{Lcd_Display(1,12,buf1,2);}
					else if(j==4*page1+1)
					{Lcd_Display(1,19,buf1,2);}
					else if(j==4*page1+2)
					{Lcd_Display(2,12,buf1,2);}
					else if(j==4*page1+3)
					{Lcd_Display(2,19,buf1,2);}
				} 
   }
}

// 0 串口无数据发送过来并且没有按翻页键‘0’ 则跳过不做任何显示
// 1 不论串口数据发送与否、按键是否翻页

void Func_Display_Channel(bit init) 
{
	unsigned char i;//函数里面定义的便便利每次进入函数是都会吧定义是的值付给他吗?
	unsigned char out_num=0;///
if(init==0)
{
	if((chuankou==0)&&(fanye==0))
		return;
	else
		{			
			chuankou=0;
			fanye=0;
		}
}

	if(ch==1)
	{
		ch=0;
		for(i=0;i<Out_Count;i++)
		{
			InOut_Buf_R[i] =InOut_Buf[i];		
		}
	}
		for(i=0;i<Out_Count;i++)
		{			
		if(InOut_Buf_R[i] !=InOut_Buf[i])
			{
				InOut_Buf_R[i] =InOut_Buf[i];
				out_num=i;
				break;
			}			
		}
		
		for(i=0;i<Out_Count;i++)
		{
			InOut_Buf_R[i] =InOut_Buf[i];		
		}
		
	if(fanye1 ==0)
	{
		if(out_num<4)
	   ddisplay(0,Out_Count);
    else if((out_num<8)&&(out_num>3))
	   ddisplay(1,Out_Count); 
		else if((out_num<12)&&(out_num>7))
	   ddisplay(2,Out_Count);
	  else if((out_num<16)&&(out_num>11))
	   ddisplay(3,Out_Count);
    else if((out_num<20)&&(out_num>15))
	   ddisplay(4,Out_Count);
	  else if((out_num<24)&&(out_num>19))
	   ddisplay(5,Out_Count);
	  else if((out_num<28)&&(out_num>23))
	   ddisplay(6,Out_Count);
		else if((out_num<32)&&(out_num>27))
	   ddisplay(7,Out_Count);
		else if((out_num<36)&&(out_num>31))
	   ddisplay(8,Out_Count);
		else if((out_num<40)&&(out_num>35))
	   ddisplay(9,Out_Count);
		else if((out_num<44)&&(out_num>39))
	   ddisplay(10,Out_Count);
		else if((out_num<48)&&(out_num>43))
	   ddisplay(11,Out_Count);
		else if((out_num<52)&&(out_num>47))
	   ddisplay(12,Out_Count);
		else if((out_num<56)&&(out_num>51))
	   ddisplay(13,Out_Count);
		else if((out_num<60)&&(out_num>55))
	   ddisplay(14,Out_Count);
		else if((out_num<64)&&(out_num>59))
	   ddisplay(15,Out_Count);
		else if((out_num<68)&&(out_num>63))
	   ddisplay(16,Out_Count);
		else if((out_num<72)&&(out_num>67))
	   ddisplay(17,Out_Count);
		else if((out_num<76)&&(out_num>71))
	   ddisplay(18,Out_Count);
		else if((out_num<80)&&(out_num>75))
	   ddisplay(19,Out_Count);
		else if((out_num<84)&&(out_num>79))
	   ddisplay(20,Out_Count);
		else if((out_num<88)&&(out_num>83))
	   ddisplay(21,Out_Count);
		else if((out_num<92)&&(out_num>87))
	   ddisplay(22,Out_Count);
		else if((out_num<96)&&(out_num>91))
	   ddisplay(23,Out_Count);
		else if((out_num<100)&&(out_num>95))
	   ddisplay(24,Out_Count);
   }
	 else
	 {
		 ddisplay(change_page,Out_Count);
		 fanye1=0;
   } 
 	switch(FUNCTION)      // DEFINE_FUNCTION_A 0X01    DEFINE_FUNCTION_G 0X04    DEFINE_FUNCTION_V 0X02                                
	{
    case 1:Lcd_Display(1,6,"A",1);
	         Lcd_Display(2,6,"A",1); 
					 break;
		case 2:Lcd_Display(1,6,"V",1);
	         Lcd_Display(2,6,"V",1);  
					 break;
		case 4:Lcd_Display(1,6,"G",1);
	         Lcd_Display(2,6,"G",1); 
					 break;
		case 3:Lcd_Display(1,6,"M",1);
	         Lcd_Display(2,6,"M",1); 
					 break;
		case 5:Lcd_Display(1,6,"M",1);
	         Lcd_Display(2,6,"M",1); 
					 break;
		case 6:Lcd_Display(1,6,"M",1);
	         Lcd_Display(2,6,"M",1);  
					 break;
		case 7:Lcd_Display(1,6,"M",1);
	         Lcd_Display(2,6,"M",1); 
			     break;
		case 0:Lcd_Display(1,6,"               ",15);
	         Lcd_Display(2,6,"               ",15); 
			     break;
		default:break;
  }
}



void Func_Display_Desk(void)
{
	Func_Display_Channel(1);
	Func_Display_InOutCall(1);
}
void Fan_Ye(void)
{
		fanye=1;
   	fanye1=1;
		change_page++;
		if(Out_Count<5)
				{if(change_page>0)change_page=0;}	
	  else if(Out_Count<9)
				{if(change_page>1)change_page=0;}
  	else if(Out_Count<13)
				{if(change_page>2)change_page=0;}
	  else if(Out_Count<17)
				{if(change_page>3)change_page=0;}
		else if(Out_Count<21)
		  	{if(change_page>4)change_page=0;}
		else if(Out_Count<25)
				{if(change_page>5)change_page=0;}
		else if(Out_Count<29)
		  	{if(change_page>6)change_page=0;}
  	else if(Out_Count<33)
		    {if(change_page>7)change_page=0;}
		else if(Out_Count<37)
		    {if(change_page>8)change_page=0;}
		else if(Out_Count<41)
		    {if(change_page>9)change_page=0;}
		else if(Out_Count<45)
		    {if(change_page>10)change_page=0;}
		else if(Out_Count<49)
		    {if(change_page>11)change_page=0;}
		else if(Out_Count<53)
		    {if(change_page>12)change_page=0;}
		else if(Out_Count<57)
		    {if(change_page>13)change_page=0;}
		else if(Out_Count<61)
		    {if(change_page>14)change_page=0;}
		else if(Out_Count<65)
		    {if(change_page>15)change_page=0;}
		else if(Out_Count<69)
		    {if(change_page>16)change_page=0;}
		else if(Out_Count<73)
		    {if(change_page>17)change_page=0;}
		else if(Out_Count<77)
		    {if(change_page>18)change_page=0;}
}

void Func_Display_Menu(void)
{
	unsigned char buf[2],r_tab;
	if(flag_lcd_update==0)return;
	flag_lcd_update = 0;
	if(flag_pos_set==1)
	{
		Lcd_Display(1,1," [1]KIR  [2]COM  [3]PRL ",24);
		Lcd_Display(2,1," [4]SYS  [5]SND         ",24);
	}
	//-------------------------------------------
	else if(flag_pos_set==11)
	{
		Lcd_Display(1,1,"Key&IR Lock:            ",24);
		Lcd_Display(2,1,"[1]Key    [2]IR   [ESC] ",24);
	}
	else if(flag_pos_set==111)
	{
		Lcd_Display(1,1,"KeyLock:                ",24);
		Lcd_Display(2,1,"[1]Lock [2]Unlock [ESC] ",24);
	}
	else if(flag_pos_set==112)
	{
		Lcd_Display(1,1,"IRLock:                 ",24);
		Lcd_Display(2,1,"[1]Lock [2]Unlock [ESC] ",24);
	}
	//---------------------------------------------
	else if(flag_pos_set==12)
	{
		Lcd_Display(1,1,"CommSetup:              ",24);
		Lcd_Display(2,1,"[1]ID [2]BautRate [ESC] ",24);
	}
	else if(flag_pos_set==121)
	{
		GetID_send();//向主机发送“ *0！”
		Lcd_Display(1,1,"DeviceID:         [OK]  ",24);
//		Lcd_Display(2,1,"          A_=>",14);
//		Lcd_Display(2,16,"   [ESC] ",9);
		Lcd_Display(2,1,"            => A",16);
		Lcd_Display(2,17,"  [ESC] ",9);
		
		delay_ms(200);//此处必须做延时处理，否则不能正常刷新显示从主机获取的设备号
		Recevied_IDdisp();//从主机获取设备ID并显示
		
		
		if(Device_ID==0)
		{
			buf[0] = '?';
//			buf[1] = '?';			
			Lcd_Display(1,15,buf,1);
		}
		else
		{
			if(tab==2)
			{
				buf[0] = Device_ID%10-1+'A';
				buf[1] = '_';
				Lcd_Display(2,16,buf,2);
			}
			else
			{
				tab = 1;
				buf[0] = Device_ID%10-1+'A';
				buf[1] = ' ';
				Lcd_Display(2,11,buf,2);
			}
		}
	}
	else if(flag_pos_set==122)
	{
		Lcd_Display(1,1,"BaudRate: 3 =>    [OK]  ",24);
		Lcd_Display(2,1,"1-24  2-48  3-96  [ESC] ",24);
		if(Baut_Rate>=1&&Baut_Rate<=3)
		{
			buf[0] = Baut_Rate+'0';
			buf[1] = '_';
			Lcd_Display(1,16,buf,2);
		}
		if(Baut_Rate_Q>=1&&Baut_Rate_Q<=3)
		{
			buf[0] = Baut_Rate_Q+'0';
			Lcd_Display(1,11,buf,1);
		}
	}
	//---------------------------------------------
	else if(flag_pos_set==13)
	{
		Lcd_Display(1,1,"PrlSet:                 ",24);
		Lcd_Display(2,1,"[1]Mode  [2]Save  [ESC] ",24);
	}
	else if(flag_pos_set==131)
	{
		Lcd_Display(1,1,"PrlMode:                ",24);
		Lcd_Display(2,1,"[1]Stop [2]Start  [ESC] ",24);
	}
	else if(flag_pos_set==132)
	{
//		Lcd_Display(1,1,"PrlTime:  No.00   [Ctrl]",24);
//		Lcd_Display(2,1,"Time: 0        [OK][ESC]",24);
		
		if(MENU_BIAOZI==1) 
	   { 
		Lcd_Display(1,1,"PrlNum: No.00      [ESC]",24);
		Lcd_Display(2,1,"  Time: 0     [OK][Ctrl]",24);

		
		
		if(tab==2)
		{
			buf[0] = '.';
			buf[1] = PRETPL_Count/10+'0';
			Lcd_Display(1,11,buf,2);
			buf[0] = PRETPL_Count%10+'0';
			buf[1] = ' ';
			Lcd_Display(1,13,buf,2);
			
			Lcd_Display(2,9,"      ",5);
			if(PRETPL_STime<10)
			{
				buf[0] = PRETPL_STime+'0';
				buf[1] = '_';
				Lcd_Display(2,9,buf,2);
			}
			else if(PRETPL_STime<100)
			{
				buf[0] = PRETPL_STime/10+'0';
				buf[1] = PRETPL_STime%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = '_';
				buf[1] = ' ';
				Lcd_Display(2,11,buf,2);
			} 
			else if(PRETPL_STime<1000)
			{
				buf[0] = PRETPL_STime/100+'0';
				buf[1] = PRETPL_STime/10%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime%10+'0';
				buf[1] = '_';
				Lcd_Display(2,11,buf,2);
			}
			else if(PRETPL_STime<10000)
			{
				buf[0] = PRETPL_STime/1000+'0';
				buf[1] = PRETPL_STime/100%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime/10%10+'0';
				buf[1] = PRETPL_STime%10+'0';
				Lcd_Display(2,11,buf,2);
				buf[0] = '_';
				buf[1] = ' ';
				Lcd_Display(2,13,buf,2);
			}
			else
			{
				buf[0] = PRETPL_STime/10000+'0';
				buf[1] = PRETPL_STime/1000%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime/100%10+'0';
				buf[1] = PRETPL_STime/10%10+'0';
				Lcd_Display(2,11,buf,2);
				buf[0] = PRETPL_STime%10+'0';
				buf[1] = ' ';
				Lcd_Display(2,13,buf,2);
			}
		}
		else
		{
			tab = 1;
			buf[0] = '.';
			buf[1] = PRETPL_Count/10+'0';
			Lcd_Display(1,11,buf,2);
			buf[0] = PRETPL_Count%10+'0';
			buf[1] = '_';
			Lcd_Display(1,13,buf,2);
			
			Lcd_Display(2,9,"     ",5);
			if(PRETPL_STime<10)
			{
				buf[0] = PRETPL_STime+'0';
				buf[1] = ' ';
				Lcd_Display(2,9,buf,2);
			}
			else if(PRETPL_STime<100)
			{
				buf[0] = PRETPL_STime/10+'0';
				buf[1] = PRETPL_STime%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = ' ';
				buf[1] = ' ';
				Lcd_Display(2,11,buf,2);
			} 
			else if(PRETPL_STime<1000)
			{
				buf[0] = PRETPL_STime/100+'0';
				buf[1] = PRETPL_STime/10%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime%10+'0';
				buf[1] = ' ';
				Lcd_Display(2,11,buf,2);
			}
			else if(PRETPL_STime<10000)
			{
				buf[0] = PRETPL_STime/1000+'0';
				buf[1] = PRETPL_STime/100%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime/10%10+'0';
				buf[1] = PRETPL_STime%10+'0';
				Lcd_Display(2,11,buf,2);
				buf[0] = ' ';
				buf[1] = ' ';
				Lcd_Display(2,13,buf,2);
			}
			else
			{
				buf[0] = PRETPL_STime/10000+'0';
				buf[1] = PRETPL_STime/1000%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime/100%10+'0';
				buf[1] = PRETPL_STime/10%10+'0';
				Lcd_Display(2,11,buf,2);
				buf[0] = PRETPL_STime%10+'0';
				buf[1] = ' ';
				Lcd_Display(2,13,buf,2);
			}
		}
	 }
	 else
		{
		      switch(flag_num_save)
		    {
		      case 1:Lcd_Display(1,1,"PrlNum: No.01      [ESC]",24);break;
		      case 2:Lcd_Display(1,1,"PrlNum: No.02      [ESC]",24);break;
		      case 3:Lcd_Display(1,1,"PrlNum: No.03      [ESC]",24);break;
		      case 4:Lcd_Display(1,1,"PrlNum: No.04      [ESC]",24);break;
		      case 5:Lcd_Display(1,1,"PrlNum: No.05      [ESC]",24);break;
		      case 6:Lcd_Display(1,1,"PrlNum: No.06      [ESC]",24);break;
		      case 7:Lcd_Display(1,1,"PrlNum: No.07      [ESC]",24);break;
		      case 8:Lcd_Display(1,1,"PrlNum: No.08      [ESC]",24);break;
		      case 9:Lcd_Display(1,1,"PrlNum: No.09      [ESC]",24);break;
		      case 10:Lcd_Display(1,1,"PrlNum: No.10      [ESC]",24);break;
		      case 11:Lcd_Display(1,1,"PrlNum: No.11      [ESC]",24);break;
		      case 12:Lcd_Display(1,1,"PrlNum: No.12      [ESC]",24);break;
		      case 13:Lcd_Display(1,1,"PrlNum: No.13      [ESC]",24);break;
		      case 14:Lcd_Display(1,1,"PrlNum: No.14      [ESC]",24);break;
		      case 15:Lcd_Display(1,1,"PrlNum: No.15      [ESC]",24);break;
		      case 16:Lcd_Display(1,1,"PrlNum: No.16      [ESC]",24);break;
		      case 17:Lcd_Display(1,1,"PrlNum: No.17      [ESC]",24);break;
		      case 18:Lcd_Display(1,1,"PrlNum: No.18      [ESC]",24);break;
		      case 19:Lcd_Display(1,1,"PrlNum: No.19      [ESC]",24);break;
		      case 20:Lcd_Display(1,1,"PrlNum: No.20      [ESC]",24);break;
		      case 21:Lcd_Display(1,1,"PrlNum: No.21      [ESC]",24);break;
					 case 22:Lcd_Display(1,1,"PrlNum: No.22      [ESC]",24);break;
		      case 23:Lcd_Display(1,1,"PrlNum: No.23      [ESC]",24);break;
		      case 24:Lcd_Display(1,1,"PrlNum: No.24      [ESC]",24);break;
		      case 25:Lcd_Display(1,1,"PrlNum: No.25      [ESC]",24);break;
		      case 26:Lcd_Display(1,1,"PrlNum: No.26      [ESC]",24);break;
		      case 27:Lcd_Display(1,1,"PrlNum: No.27      [ESC]",24);break;
		      case 28:Lcd_Display(1,1,"PrlNum: No.28      [ESC]",24);break;
					case 29:Lcd_Display(1,1,"PrlNum: No.29      [ESC]",24);break;
		      case 30:Lcd_Display(1,1,"PrlNum: No.30      [ESC]",24);break;
		      case 31:Lcd_Display(1,1,"PrlNum: No.31      [ESC]",24);break;
		      case 32:Lcd_Display(1,1,"PrlNum: No.32      [ESC]",24);break;
					default:Lcd_Display(1,1,"PrlNum: No.00      [ESC]",24);break;
		       }
		Lcd_Display(2,1,"  Time: 0     [OK][Ctrl]",24);

			PRETPL_Count = flag_num_save;			
			if(tab!=r_tab)
			{
			 PRETPL_STime=0;
       r_tab = tab;			
 			}
 		 	Lcd_Display(2,9,"      ",6);
		if(tab==2)
		{
			buf[0] = '.';
			buf[1] = PRETPL_Count/10+'0';
			Lcd_Display(1,11,buf,2);
			buf[0] = PRETPL_Count%10+'0';
			buf[1] = ' ';
			Lcd_Display(1,13,buf,2);
			
			Lcd_Display(2,9,"      ",5);
			if(PRETPL_STime<10)
			{
				buf[0] = PRETPL_STime+'0';
				buf[1] = '_';
				Lcd_Display(2,9,buf,2);
			}
			else if(PRETPL_STime<100)
			{
				buf[0] = PRETPL_STime/10+'0';
				buf[1] = PRETPL_STime%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = '_';
				buf[1] = ' ';
				Lcd_Display(2,11,buf,2);
			} 
			else if(PRETPL_STime<1000)
			{
				buf[0] = PRETPL_STime/100+'0';
				buf[1] = PRETPL_STime/10%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime%10+'0';
				buf[1] = '_';
				Lcd_Display(2,11,buf,2);
			}
			else if(PRETPL_STime<10000)
			{
				buf[0] = PRETPL_STime/1000+'0';
				buf[1] = PRETPL_STime/100%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime/10%10+'0';
				buf[1] = PRETPL_STime%10+'0';
				Lcd_Display(2,11,buf,2);
				buf[0] = '_';
				buf[1] = ' ';
				Lcd_Display(2,13,buf,2);
			}
			else
			{
				buf[0] = PRETPL_STime/10000+'0';
				buf[1] = PRETPL_STime/1000%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime/100%10+'0';
				buf[1] = PRETPL_STime/10%10+'0';
				Lcd_Display(2,11,buf,2);
				buf[0] = PRETPL_STime%10+'0';
				buf[1] = ' ';
				Lcd_Display(2,13,buf,2);
			}
		}
		else
		{
			tab = 1;
			buf[0] = '.';
			buf[1] = PRETPL_Count/10+'0';
			Lcd_Display(1,11,buf,2);
			buf[0] = PRETPL_Count%10+'0';
			buf[1] = '_';
			Lcd_Display(1,13,buf,2);
			
			Lcd_Display(2,9,"     ",5);
			if(PRETPL_STime<10)
			{
				buf[0] = PRETPL_STime+'0';
				buf[1] = ' ';
				Lcd_Display(2,9,buf,2);
			}
			else if(PRETPL_STime<100)
			{
				buf[0] = PRETPL_STime/10+'0';
				buf[1] = PRETPL_STime%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = ' ';
				buf[1] = ' ';
				Lcd_Display(2,11,buf,2);
			} 
			else if(PRETPL_STime<1000)
			{
				buf[0] = PRETPL_STime/100+'0';
				buf[1] = PRETPL_STime/10%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime%10+'0';
				buf[1] = ' ';
				Lcd_Display(2,11,buf,2);
			}
			else if(PRETPL_STime<10000)
			{
				buf[0] = PRETPL_STime/1000+'0';
				buf[1] = PRETPL_STime/100%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime/10%10+'0';
				buf[1] = PRETPL_STime%10+'0';
				Lcd_Display(2,11,buf,2);
				buf[0] = ' ';
				buf[1] = ' ';
				Lcd_Display(2,13,buf,2);
			}
			else
			{
				buf[0] = PRETPL_STime/10000+'0';
				buf[1] = PRETPL_STime/1000%10+'0';
				Lcd_Display(2,9,buf,2);
				buf[0] = PRETPL_STime/100%10+'0';
				buf[1] = PRETPL_STime/10%10+'0';
				Lcd_Display(2,11,buf,2);
				buf[0] = PRETPL_STime%10+'0';
				buf[1] = ' ';
				Lcd_Display(2,13,buf,2);
			}
		}
	 }
	}
	//---------------------------------------------
	else if(flag_pos_set==14)
	{
		Lcd_Display(1,1,"System:                 ",24);
		Lcd_Display(2,1,"[1]Reset[2]LcdSaver[ESC]",24);
	}
	else if(flag_pos_set==141)
	{
		Lcd_Display(1,1,"Reset:            [OK]  ",24);
		Lcd_Display(2,1,"SystemInitialize  [ESC] ",24);
	}
	else if(flag_pos_set==142)
	{
		Lcd_Display(1,1,"ScreenSaver:            ",24);
		Lcd_Display(2,1,"[1]Stop   [2]Start [ESC]",24);
	}
	//---------------------------------------------
	else if(flag_pos_set==15)
	{
		Lcd_Display(1,1,"SoundMode:              ",24);
		Lcd_Display(2,1,"[1]OFF   [2]ON    [ESC] ",24);
	}
	else if(flag_pos_set>1000)
	{
		Lcd_Display(1,1,"                        ",24);
		Lcd_Display(2,1,"        Done....        ",24);
		delay_ms(300);
		save_pre_successful();
		delay_ms(700);
		if(flag_pos_set==1310||flag_pos_set==1320)
		{
			flag_pos_set = flag_pos_set/10;
		}
		else 
		{
			flag_pos_set = flag_pos_set/100;
		}
		flag_lcd_update = 1;
	}
	else if(flag_pos_set==232)
	{
		
			Lcd_Display(1,1,"                        ",24);
			Lcd_Display(2,1,"        Error....       ",24);
			delay_ms(700);
			flag_pos_set = 132;

			flag_lcd_update = 1;

	}
}

/////
/////
void Func_Display_MenuCal(unsigned char cal)
{ 
	flag_lcd_update = 1;
	if(flag_pos_set==1)
	{
		if(cal>=KEY_1&&cal<=KEY_5)
		{
			flag_pos_set = flag_pos_set*10+cal;
		}
	}
	//-------------------------------------------
	else if(flag_pos_set==11)
	{
		if(cal>=KEY_1&&cal<=KEY_2)
		{
			flag_pos_set = flag_pos_set*10+cal;
		}
	}
	else if(flag_pos_set==111)
	{
		if(cal>=KEY_1&&cal<=KEY_2)
		{
			flag_pos_set = flag_pos_set*10+cal;
		}
		if(flag_pos_set==1111)
		{		Lock_Key=1;
         I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_LOCK_KEY,&Lock_Key,1);
    }
		if(flag_pos_set==1112)
		{		
				Lock_Key=0;
        I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_LOCK_KEY,&Lock_Key,1);
		}
	}

	else if(flag_pos_set==112)
	{
		if(cal>=KEY_1&&cal<=KEY_2)
		{
				flag_pos_set = flag_pos_set*10+cal;
				if(flag_pos_set==1121)
				{	
					Lock_IR=1;
					I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_LOCK_IR,&Lock_IR,1);
				}
				if(flag_pos_set==1122)
				{		Lock_IR=0;
						I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_LOCK_IR,&Lock_IR,1);
				}
		}
	}
	//---------------------------------------------
	else if(flag_pos_set==12)
	{
			Baut_Rate = 3;
			Device_ID = 01;

		if(cal>=KEY_1&&cal<=KEY_2)
		{
			flag_pos_set = flag_pos_set*10+cal;
//			Device_ID = 01;
//			Baut_Rate = 3;
			I2CBus_ReadToBuf(DEFINE_EEP_ADDR_BAUT_RATE,&Baut_Rate_Q,1);

			tab = 2;
		}
	}
	else if(flag_pos_set==121)
	{
		
		if(cal>=KEY_1&&cal<=KEY_9)
		{
			if(tab==2)
				Device_ID = Device_ID/10*10+cal;
//			else 
//			{
//				tab=1;
//				Device_ID = Device_ID%10 + 10*cal;
//			}
		}
	
//		else if(cal==KEY_0)
//		{
//			if(tab==1)
//				Device_ID = Device_ID%10;
//		}
		 if(cal==KEY_OK)
		{
			flag_pos_set = flag_pos_set*10;
			Switch_Modify_DeviceID(Device_ID);
		}
//		else if(cal==KEY_CTRL)
//		{
//			if(tab==1)tab=2;
//			else tab=1;
//		}
	}
	else if(flag_pos_set==122)
	{
		if(cal>=KEY_1&&cal<=KEY_3)
		{
			Baut_Rate = cal;
		}
		else if(cal==KEY_OK)
		{
//			flag_pos_set = flag_pos_set*10;//////////////////
			Baut_Rate_Q = Baut_Rate;
			I2CBus_WriteFromBuf(DEFINE_EEP_ADDR_BAUT_RATE,&Baut_Rate_Q,1);//

			Switch_Modify_BaudRate(Baut_Rate);
		}
	}
	//---------------------------------------------
	else if(flag_pos_set==13)
	{
		if(cal>=KEY_1&&cal<=KEY_2)
		{
			flag_pos_set = flag_pos_set*10+cal;
			PRETPL_Count = 0;
			PRETPL_STime = 0;
			tab = 1;
		}
	}
	else if(flag_pos_set==131)
	{
		if(cal==KEY_2)
		{
			flag_pos_set = flag_pos_set*10;
			Func_Pre_cmd(1);
		}
		else if(cal==KEY_1)
		{
			flag_pos_set = flag_pos_set*10;
			Func_Pre_cmd(0);
		}
	}
	else if(flag_pos_set==132)
	{
	if(MENU_BIAOZI==1)
	{
			if(cal>=KEY_1&&cal<=KEY_9)
		{
 			if(tab==2)
 			{
				if(PRETPL_STime<6000)PRETPL_STime = PRETPL_STime*10+cal;/////////////////////////
				else PRETPL_STime = 60000;
				if(PRETPL_STime>60000)PRETPL_STime = 60000;
 			}
 			else 
 			{
 				tab=1;
 				if(PRETPL_Count<10)PRETPL_Count = PRETPL_Count*10+cal;
 				else PRETPL_Count = 32;
 				if(PRETPL_Count>32)PRETPL_Count = 32;
 			}
		}
		else if(cal==KEY_0)
		{
 			if(tab==2)
 			{
				if(PRETPL_STime<6000)PRETPL_STime = PRETPL_STime*10;
				else PRETPL_STime = 60000;
				if(PRETPL_STime>60000)PRETPL_STime = 60000;
 			}
 			else 
 			{
 				tab=1;
 				if(PRETPL_Count<10)PRETPL_Count = PRETPL_Count*10;
 				else PRETPL_Count = 32;
 				if(PRETPL_Count>32)PRETPL_Count = 32;
 			}
		}
		else if(cal==KEY_OK)
		{
			if(PRETPL_Count>0&&PRETPL_Count<33)
			{
				flag_pos_set = flag_pos_set*10;
				Func_Save_pre(PRETPL_Count,PRETPL_STime);
			}
			
			if(PRETPL_Count == 0)//这里是不通过按键保存预案，当预案号为0时，显示error
			{
					flag_pos_set = flag_pos_set + 100;

			}
		}
		else if(cal==KEY_CTRL)
		{
			if(tab==1)tab=2;
			else 
			{
				tab=1;
 				PRETPL_Count = 0;
 				PRETPL_STime = 0;
			}
		}		
	}
	
	else
	{
		
		if(cal>=KEY_1&&cal<=KEY_9)
		{
				if(tab==2)
 			{
				if(PRETPL_STime<6000)PRETPL_STime = PRETPL_STime*10+cal;/////////////////////////
				else PRETPL_STime = 60000;
				if(PRETPL_STime>60000)PRETPL_STime = 60000;
 			}
 			else 
 			{
 				tab=1;
 				if(PRETPL_Count<10)PRETPL_Count = PRETPL_Count*10+cal;
 				else PRETPL_Count = 32;
 				if(PRETPL_Count>32)PRETPL_Count = 32;
 			}
		}
		else if(cal==KEY_0)
		{
				if(tab==2)
 			{
				if(PRETPL_STime<6000)PRETPL_STime = PRETPL_STime*10;
				else PRETPL_STime = 60000;
				if(PRETPL_STime>60000)PRETPL_STime = 60000;
 			}
 			else 
 			{
 				tab=1;
 				if(PRETPL_Count<10)PRETPL_Count = PRETPL_Count*10;
 				else PRETPL_Count = 32;
 				if(PRETPL_Count>32)PRETPL_Count = 32;
 			}
		}
		else if(cal==KEY_OK)
		{
			if(PRETPL_Count>0&&PRETPL_Count<33)
			{
				flag_pos_set = flag_pos_set*10;
				Func_Save_pre(PRETPL_Count,PRETPL_STime);
			}
			if(PRETPL_Count == 0)//这里是不通过按键保存预案，当预案号为0时，显示error
			{
					flag_pos_set = flag_pos_set + 100;

			}

		}
		else if(cal==KEY_CTRL)
		{
			if(tab==1)tab=2;
			else 
			{
				tab=1;
				PRETPL_STime = 0;
				flag_num_save = 0;
				PRETPL_Count = 0;
		  }
		}
	}
	
}
	//---------------------------------------------
	else if(flag_pos_set==14)
	{
		if(cal>=KEY_1&&cal<=KEY_2)
		{
			flag_pos_set = flag_pos_set*10+cal;
		}
	}
	else if(flag_pos_set==141)
	{
		if(cal==KEY_OK)
		{
			flag_pos_set = flag_pos_set*10;
			Lock_Init();
			
			fuwei=1;
			Switch_Modify_SystemInitialize();
		}
	}
	else if(flag_pos_set==142)
	{
		if(cal==KEY_2)
		{
			flag_pos_set = flag_pos_set*100;
			LCDS_Enable = 1;
			Func_Modify_LcdSaver();
		}
		else if(cal==KEY_1)
		{
			flag_pos_set = flag_pos_set*100;
			LCDS_Enable = 0;
			Func_Modify_LcdSaver();
		}
	}
	//---------------------------------------------
	else if(flag_pos_set==15)
	{
		if(cal==KEY_2)
		{
			flag_pos_set = flag_pos_set*100;
			Sound_ENB = 1;
			Func_Modify_Sound();
		}
		else if(cal==KEY_1)
		{
			flag_pos_set = flag_pos_set*100;
			Sound_ENB = 0;
			Func_Modify_Sound();
		}
   }
	
}


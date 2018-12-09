/******************************************************************************
 * MenuAction.H - 菜单扩展功能代码
 ******************************************************************************/

/********************** **********  *****************************************/

void MenuActionNULL(int8 key)
{
 	key =key; 
}

/******************************** 设置时间  **********************************/
void Func_Set_Clock(u8 key)
{
	u8 pos = 0,cnt = 0,buf[17],flag=0,flag_r=0;
	Func_LCD_RowClearWriteString16(1,1,"Set Clock:\0");
	Func_LCD_RowClearWriteString16(2,1,"\0");
	while(1)
	{
		if(Timer2_Sec_Temp<(DEFINE_TIM_LCD_REFLASH/2))
		{
			flag_r = 0;
			if(flag == 0)
			{
				flag = 1;
				cnt = 0;
				buf[cnt++] = m_hour/10%10 + '0';
				buf[cnt++] = m_hour%10 + '0';
				buf[cnt++] = ':';
				buf[cnt++] = m_minute/10%10 + '0';
				buf[cnt++] = m_minute%10 + '0';
				buf[cnt++] = ':';
				buf[cnt++] = m_second/10%10 + '0';
				buf[cnt++] = m_second%10 + '0';
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,5,buf);
			}
		}
		else
		{
			flag = 0;
			if(flag_r == 0)
			{
				flag_r = 1;
				cnt = 0;
				if(pos==0)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				if(pos==1)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				if(pos==2)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,5,buf);
			}
		}
		key = Func_Get_Push_Key_Val();
		if(key!=0xff)
		{
			if(key == KEY_ESC)
			{
				if(pos)pos--;
				else return;
			}
			else if(key == KEY_OK)
			{
				pos++;
				if(pos>3)
				{
					DS1302_Set_Time(m_hour,m_minute,m_second);
					return;
				}
			}
			else if(key == KEY_INC)
			{
				if(pos==0)
				{
					m_hour++;
					if(m_hour>23)m_hour=0;
				}
				else if(pos==1)
				{
					m_minute++;
					if(m_minute>59)m_minute=0;
				}
				else if(pos==2)
				{
					m_second++;
					if(m_second>59)m_second=0;
				}
			}
			else if(key == KEY_DEC)
			{
				if(pos==0)
				{
					if(m_hour)m_hour--;
					else m_hour = 23;
				}
				else if(pos==1)
				{
					if(m_minute)m_minute--;
					else m_minute = 59;
				}
				else if(pos==2)
				{
					if(m_second)m_second--;
					else m_second = 59;
				}
			}
		}
	}
}

void Func_Set_Date(u8 key)
{
	u8 pos = 0,cnt = 0,buf[17],flag=0,flag_r=0;
	Func_LCD_RowClearWriteString16(1,1,"Set Date:\0");
	Func_LCD_RowClearWriteString16(2,1,"\0");
	while(1)
	{
		if(Timer2_Sec_Temp<(DEFINE_TIM_LCD_REFLASH/2))
		{
			flag_r = 0;
			if(flag == 0)
			{
				flag = 1;
				cnt = 0;
				buf[cnt++] = m_year/10%10 + '0';
				buf[cnt++] = m_year%10 + '0';
				buf[cnt++] = '-';
				buf[cnt++] = m_month/10%10 + '0';
				buf[cnt++] = m_month%10 + '0';
				buf[cnt++] = '-';
				buf[cnt++] = m_day/10%10 + '0';
				buf[cnt++] = m_day%10 + '0';
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,5,buf);
			}
		}
		else
		{
			flag = 0;
			if(flag_r == 0)
			{
				flag_r = 1;
				cnt = 0;
				if(pos==0)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				if(pos==1)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				if(pos==2)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,5,buf);
			}
		}
		key = Func_Get_Push_Key_Val();
		if(key!=0xff)
		{
			if(key == KEY_ESC)
			{
				if(pos)pos--;
				else return;
			}
			else if(key == KEY_OK)
			{
				pos++;
				if(pos>3)
				{
					DS1302_Set_Date(m_year,m_month,m_day);
					return;
				}
			}
			else if(key == KEY_INC)
			{
				if(pos==0)
				{
					m_year++;
					if(m_year>99)m_year=0;
				}
				else if(pos==1)
				{
					m_month++;
					if(m_month>12)m_month=1;
				}
				else if(pos==2)
				{
					m_day++;
					if(m_day>31)m_day=1;
				}
			}
			else if(key == KEY_DEC)
			{
				if(pos==0)
				{
					if(m_year)m_year--;
					else m_year = 99;
				}
				else if(pos==1)
				{
					if(m_month>1)m_month--;
					else m_month = 12;
				}
				else if(pos==2)
				{
					if(m_day>1)m_day--;
					else m_day = 31;
				}
			}
		}
	}
}

void Func_Set_Temper(u8 key)
{
	u8 pos = 0,cnt = 0,buf[17],flag=0,flag_r=0;
	Func_LCD_RowClearWriteString16(1,1,"Set Temper:\0");
	Func_LCD_RowClearWriteString16(2,1,"\0");
	while(1)
	{
		if(Timer2_Sec_Temp<(DEFINE_TIM_LCD_REFLASH/2))
		{
			flag_r = 0;
			if(flag == 0)
			{
				flag = 1;
				cnt = 0;
				buf[cnt++] = 'H';
				buf[cnt++] = ':';
				buf[cnt++] = m_para.temp_h/10%10 + '0';
				buf[cnt++] = m_para.temp_h%10 + '0';
				buf[cnt++] = 0xDF;
				buf[cnt++] = ' ';
				buf[cnt++] = ' ';
				buf[cnt++] = 'L';
				buf[cnt++] = ':';
				buf[cnt++] = m_para.temp_l/10%10 + '0';
				buf[cnt++] = m_para.temp_l%10 + '0';
				buf[cnt++] = 0xDF;
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,3,buf);
			}
		}
		else
		{
			flag = 0;
			if(flag_r == 0)
			{
				flag_r = 1;
				cnt = 0;
				cnt++;
				cnt++;
				if(pos==0)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				cnt++;
				cnt++;
				cnt++;
				cnt++;
				if(pos==1)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,3,buf);
			}
		}
		key = Func_Get_Push_Key_Val();
		if(key!=0xff)
		{
			if(key == KEY_ESC)
			{
				if(pos)pos--;
				else return;
			}
			else if(key == KEY_OK)
			{
				pos++;
				if(pos>2)
				{
					System_Para_Save();
					return;
				}
			}
			else if(key == KEY_INC)
			{
				if(pos==0)
				{
					m_para.temp_h++;
					if(m_para.temp_h>99)m_para.temp_h=m_para.temp_l;
				}
				else if(pos==1)
				{
					m_para.temp_l++;
					if(m_para.temp_l>m_para.temp_h)m_para.temp_l=m_para.temp_h;
				}
			}
			else if(key == KEY_DEC)
			{
				if(pos==0)
				{
					if(m_para.temp_h>m_para.temp_l)m_para.temp_h--;
					else m_para.temp_h = 99;
				}
				else if(pos==1)
				{
					if(m_para.temp_l)m_para.temp_l--;
					else m_para.temp_l = m_para.temp_h;
				}
			}
		}
	}
}

void Func_Set_Rhum(u8 key)
{
	u8 pos = 0,cnt = 0,buf[17],flag=0,flag_r=0;
	Func_LCD_RowClearWriteString16(1,1,"Set Rhum:\0");
	Func_LCD_RowClearWriteString16(2,1,"\0");
	while(1)
	{
		if(Timer2_Sec_Temp<(DEFINE_TIM_LCD_REFLASH/2))
		{
			flag_r = 0;
			if(flag == 0)
			{
				flag = 1;
				cnt = 0;
				buf[cnt++] = 'H';
				buf[cnt++] = ':';
				buf[cnt++] = m_para.rhum_h/10%10 + '0';
				buf[cnt++] = m_para.rhum_h%10 + '0';
				buf[cnt++] = '%';
				buf[cnt++] = ' ';
				buf[cnt++] = ' ';
				buf[cnt++] = 'L';
				buf[cnt++] = ':';
				buf[cnt++] = m_para.rhum_l/10%10 + '0';
				buf[cnt++] = m_para.rhum_l%10 + '0';
				buf[cnt++] = '%';
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,3,buf);
			}
		}
		else
		{
			flag = 0;
			if(flag_r == 0)
			{
				flag_r = 1;
				cnt = 0;
				cnt++;
				cnt++;
				if(pos==0)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				cnt++;
				cnt++;
				cnt++;
				cnt++;
				if(pos==1)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,3,buf);
			}
		}
		key = Func_Get_Push_Key_Val();
		if(key!=0xff)
		{
			if(key == KEY_ESC)
			{
				if(pos)pos--;
				else return;
			}
			else if(key == KEY_OK)
			{
				pos++;
				if(pos>2)
				{
					System_Para_Save();
					return;
				}
			}
			else if(key == KEY_INC)
			{
				if(pos==0)
				{
					m_para.rhum_h++;
					if(m_para.rhum_h>99)m_para.rhum_h=m_para.rhum_l;
				}
				else if(pos==1)
				{
					m_para.rhum_l++;
					if(m_para.rhum_l>m_para.rhum_h)m_para.rhum_l=m_para.rhum_h;
				}
			}
			else if(key == KEY_DEC)
			{
				if(pos==0)
				{
					if(m_para.rhum_h>m_para.rhum_l)m_para.rhum_h--;
					else m_para.rhum_h = 99;
				}
				else if(pos==1)
				{
					if(m_para.rhum_l)m_para.rhum_l--;
					else m_para.rhum_l = m_para.rhum_h;
				}
			}
		}
	}
}
void Func_Set_o3_tim(u8 key)
{
	u8 pos = 0,cnt = 0,buf[17],flag=0,flag_r=0;
	Func_LCD_RowClearWriteString16(1,1,"Set o3_tim:\0");
	Func_LCD_RowClearWriteString16(2,1,"\0");
	while(1)
	{
		if(Timer2_Sec_Temp<(DEFINE_TIM_LCD_REFLASH/2))
		{
			flag_r = 0;
			if(flag == 0)
			{
				flag = 1;
				cnt = 0;
				buf[cnt++] = m_para.o3_tim_m/10%10 + '0';
				buf[cnt++] = m_para.o3_tim_m%10 + '0';
				buf[cnt++] = ':';
				buf[cnt++] = m_para.o3_tim_s/10%10 + '0';
				buf[cnt++] = m_para.o3_tim_s%10 + '0';
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,7,buf);
			}
		}
		else
		{
			flag = 0;
			if(flag_r == 0)
			{
				flag_r = 1;
				cnt = 0;
				if(pos==0)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				cnt++;
				if(pos==1)
				{
					buf[cnt++] = ' ';
					buf[cnt++] = ' ';
				}
				else
				{
					cnt++;
					cnt++;
				}
				buf[cnt++] = 0;
				Func_LCD_RowClearWriteString16(2,7,buf);
			}
		}
		key = Func_Get_Push_Key_Val();
		if(key!=0xff)
		{
			if(key == KEY_ESC)
			{
				if(pos)pos--;
				else return;
			}
			else if(key == KEY_OK)
			{
				pos++;
				if(pos>2)
				{
					System_Para_Save();
					return;
				}
			}
			else if(key == KEY_INC)
			{
				if(pos==0)
				{
					m_para.o3_tim_m++;
					if(m_para.o3_tim_m>59)m_para.o3_tim_m=0;
				}
				else if(pos==1)
				{
					m_para.o3_tim_s++;
					if(m_para.o3_tim_s>59)m_para.o3_tim_s=0;
				}
			}
			else if(key == KEY_DEC)
			{
				if(pos==0)
				{
					if(m_para.o3_tim_m)m_para.o3_tim_m--;
					else m_para.o3_tim_m = 59;
				}
				else if(pos==1)
				{
					if(m_para.o3_tim_s)m_para.o3_tim_s--;
					else m_para.o3_tim_s = 59;
				}
			}
		}
	}
}
/******************************* End of File **********************************/

#ifndef __LCDXX02_H__ 
#define __LCDXX02_H__

void Lcd_Init(void);
void Lcd_Display(unsigned char Row,unsigned char Col,unsigned char *Data_P,unsigned char Num);
void Func_LCD_WriteString16(unsigned char row,unsigned char col,unsigned char *pDat);
void Func_LCD_RowClearWriteString(unsigned char row,unsigned char col,unsigned char *pDat,unsigned char num);
void Func_LCD_RowClearWriteString16(unsigned char row,unsigned char col,unsigned char *pDat);
void Func_LCD_Init_Screen(void);

//#define Lcd_Light  P64      
//#define Lcd_RS  	 P65     
//#define Lcd_RW     P66     	
//#define Lcd_E      P67   
//#define Lcd_Data0  P32  
//#define Lcd_Data1  P34
//#define Lcd_Data2  P50
//#define Lcd_Data3  P51
//#define Lcd_Data4  P35
//#define Lcd_Data5  P36
//#define Lcd_Data6  P37
//#define Lcd_Data7  P70

#define Lcd_RS  	 P27     
#define Lcd_RW     P26     	
#define Lcd_E      P25   
#define Lcd_Data0  P00  
#define Lcd_Data1  P01
#define Lcd_Data2  P02
#define Lcd_Data3  P03
#define Lcd_Data4  P04
#define Lcd_Data5  P05
#define Lcd_Data6  P06
#define Lcd_Data7  P07

void Set_LCD_Data(unsigned char Dat)
{
	if(Dat & 0x01)
	{
		Lcd_Data0 = 1;    
	}
	else
	{
		Lcd_Data0 = 0; 
	}
	if(Dat & 0x02)
	{
		Lcd_Data1 = 1;    
	}
	else
	{
		Lcd_Data1 = 0; 
	}
	if(Dat & 0x04)
	{
		Lcd_Data2 = 1;    
	}
	else
	{
		Lcd_Data2 = 0; 
	}
	if(Dat & 0x08)
	{
		Lcd_Data3 = 1;    
	}
	else
	{
		Lcd_Data3 = 0; 
	}
	if(Dat & 0x10)
	{
		Lcd_Data4 = 1;    
	}
	else
	{
		Lcd_Data4 = 0; 
	}
	if(Dat & 0x20)
	{
		Lcd_Data5 = 1;    
	}
	else
	{
		Lcd_Data5 = 0; 
	}
	if(Dat & 0x40)
	{
		Lcd_Data6 = 1;    
	}
	else
	{
		Lcd_Data6 = 0; 
	}
	if(Dat & 0x80)
	{
		Lcd_Data7 = 1;    
	}
	else
	{
		Lcd_Data7 = 0; 
	}
}

void Lcd_Init(void)	
{
	Lcd_E = 0;
	Delay_Ms(2);
	Lcd_RS = 0;
	Lcd_RW = 0;	
	Set_LCD_Data(0x38);		
	Lcd_E = 1;	            
	Delay_Ms(2);	
	Lcd_RS = 0;
	Lcd_RW = 0;
	Lcd_E  = 0;
	Set_LCD_Data(0x01);		
	Lcd_E  = 0;		
	Delay_Ms(2); 
	Lcd_RS = 0;
	Lcd_RW = 0;
	Lcd_E  = 0;
	Set_LCD_Data(0x0C);		
	Lcd_E  = 1;		
	Delay_Ms(2);

	Lcd_RS = 0;
	Lcd_RW = 0;
	Lcd_E  = 0;
	Set_LCD_Data(0x06);		
	Lcd_E  = 1;		
	Delay_Ms(2);
	Lcd_E = 0;	
	
	Delay_Ms(20);
	Func_LCD_Init_Screen();
} 

void Lcd_Display(unsigned char Row,unsigned char Col,unsigned char *Data_P,unsigned char Num)
{
	unsigned char i = 0,t = 10,flag = 0;	
	Set_LCD_Data(0x00);
	Lcd_E = 0;	        
	Col--;
	if(Row == 2)
		Row = 0xC0;    
	else
		Row = 0x80;
	Set_LCD_Data(Row | Col);	
	Lcd_RS= 0;
	Lcd_RW= 0;
	Lcd_E= 1;   		
	Delay_Us(t);
	Lcd_E = 0;	
	for(i = 0;i < Num;i++)
	{
    Set_LCD_Data(*Data_P);
		Data_P++;
		Lcd_RS= 1;
		Lcd_RW= 0;
		Lcd_E= 1;   	 
		Delay_Us(t); 
		Lcd_E= 0;     
	}
}

void Func_LCD_WriteString16(unsigned char row,unsigned char col,unsigned char *pDat)
{
	Lcd_Display(row,col,pDat,16);
}

void Func_LCD_RowClearWriteString16(unsigned char row,unsigned char col,unsigned char *pDat)
{
	unsigned char i=0;
	Lcd_Display(row,col,"                \0",16);
	while(pDat[i])i++;
	Lcd_Display(row,col,pDat,i);
}
void Func_LCD_RowClearWriteString(unsigned char row,unsigned char col,unsigned char *pDat,unsigned char num)
{
//	Lcd_Display(row,col,"                \0",num);
	Lcd_Display(row,col,pDat,num);
}

void Func_LCD_Init_Screen(void)
{
	Lcd_Display(1,1,"   SystemInit   \0",16);
	Lcd_Display(2,1,"  PleaseWating  \0",16);
}
#endif


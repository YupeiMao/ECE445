typedef unsigned char  u8; 
typedef unsigned int   u16; 
typedef unsigned long  u32; 

typedef char  int8; 
typedef int   int16; 
typedef long  int32; 

#define NULL 0

typedef enum{
	C51_ERR = 0,
	C51_ERR_OK,
	C51_ERR_TIMEOUT
}C51_TYPE_ERR;       //ERROR变量定义

#define ROMDATA	code
#define XDATA	  xdata

#define Uart_Buffer_Size 512 
#define Uart_Timout_Max  5//N*2ms
#define Channel_Max      128
typedef struct
{
	u8  uart_recv_timout;
	u16 uart_cnt;
	u8  uart_Buf[Uart_Buffer_Size];
	u16 uart_dat_len;
	u8  uart_dat[Uart_Buffer_Size];
	u8  temp_h;
	u8  temp_l;
	u8  rhum_h;
	u8  rhum_l;
	u8  o3_tim_m;
	u8  o3_tim_s;
	u16 o3_tim;
	
}m_TypeDef;

extern m_TypeDef xdata m_para;

#define DEFINE_TIM_LCD_REFLASH 500
extern u16 Timer2_Sec_Temp;
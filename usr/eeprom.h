typedef bit BOOL;
typedef unsigned char BYTE;
typedef unsigned int WORD;

#define ERROR   0
#define OK      1

//-----------------------------------------------


sfr IAP_DATA    =   0xC2;           //IAP数据寄存器
sfr IAP_ADDRH   =   0xC3;           //IAP地址寄存器高字节
sfr IAP_ADDRL   =   0xC4;           //IAP地址寄存器低字节
sfr IAP_CMD     =   0xC5;           //IAP命令寄存器
sfr IAP_TRIG    =   0xC6;           //IAP命令触发寄存器
sfr IAP_CONTR   =   0xC7;           //IAP控制寄存器


#define CMD_IDLE    0               //空闲模式
#define CMD_READ    1               //IAP字节读命令
#define CMD_PROGRAM 2               //IAP字节编程命令
#define CMD_ERASE   3               //IAP扇区擦除命令

//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

//void IapIdle();
//BYTE IapReadByte(WORD addr);
//void IapProgramByte(WORD addr, BYTE dat);
//void IapEraseSector(WORD addr);


#define EEPROM_LEN_MAX     10

#define EEPROM_ADDR        0xC000// 0X0400

BYTE xdata eeprom_buffer[EEPROM_LEN_MAX];

#if 1
/*----------------------------
关闭IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //关闭IAP功能
    IAP_CMD = 0;                    //清除命令寄存器
    IAP_TRIG = 0;                   //清除触发寄存器
    IAP_ADDRH = 0x80;               //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}

/*----------------------------
从ISP/IAP/EEPROM区域读取一字节
----------------------------*/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //数据缓冲区

    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_READ;             //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    dat = IAP_DATA;                 //读ISP/IAP/EEPROM数据
    IapIdle();                      //关闭IAP功能

    return dat;                     //返回
}

/*----------------------------
写一字节数据到ISP/IAP/EEPROM区域
----------------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_PROGRAM;          //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_DATA = dat;                 //写ISP/IAP/EEPROM数据
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}

/*----------------------------
扇区擦除
----------------------------*/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;         //使能IAP
    IAP_CMD = CMD_ERASE;            //设置IAP命令
    IAP_ADDRL = addr;               //设置IAP低地址
    IAP_ADDRH = addr >> 8;          //设置IAP高地址
    IAP_TRIG = 0x5a;                //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                //写触发命令(0xa5)
    _nop_();                        //等待ISP/IAP/EEPROM操作完成
    IapIdle();
}

BYTE eeprom_read(WORD begin_addr, WORD counter, BYTE array[])
{
    WORD i = 0;
    WORD in_sector_begin_addr = 0;
    WORD sector_addr = 0;
    WORD byte_addr = 0;

    /* 判是否是有效范围,此函数不允许跨扇区操作 */
    if(counter > EEPROM_LEN_MAX)
        return ERROR;
    in_sector_begin_addr = begin_addr & 0x01ff;
    /* 假定从扇区的第0个字节开始，到USED_BYTE_QTY_IN_ONE_SECTOR-1个字节结束,后面部分不用,程序易编写 */
    if((in_sector_begin_addr + counter) > EEPROM_LEN_MAX)
        return ERROR;

    /* 将该扇区数据 0 - (USED_BYTE_QTY_IN_ONE_SECTOR-1) 字节数据读入缓冲区保护 */
    sector_addr = (begin_addr & 0xfe00);
    byte_addr = sector_addr;

    for(i = 0; i < counter; i++)
    {
        array[i] = IapReadByte(byte_addr++);
    }
    return  OK;
}

/* 写数据进 数据Flash存储器, 只在同一个扇区内写，不保留原有数据 */
/* begin_addr,被写数据Flash开始地址；counter,连续写多少个字节； array[]，数据来源   */
BYTE eeprom_write(WORD begin_addr, WORD counter, BYTE array[])
{
    WORD i = 0;
    WORD in_sector_begin_addr = 0;
    WORD sector_addr = 0;

    /* 判是否是有效范围,此函数不允许跨扇区操作 */
    if(counter > EEPROM_LEN_MAX)
        return  ERROR;
    in_sector_begin_addr = begin_addr & 0x01ff;
    if((in_sector_begin_addr + counter) > EEPROM_LEN_MAX)
        return ERROR;

    /* 擦除 要修改/写入 的扇区 */
    IapEraseSector(begin_addr);

    for(i=0; i<counter; i++)
    {
        /* 写一个字节 */
        IapProgramByte(begin_addr, array[i]);
        /*  比较对错 */
        if (IapReadByte(begin_addr) != array[i])
        {
            IapIdle();
            return ERROR;
        }
        begin_addr++;
    }
    IapIdle();
    return  OK;
}
#endif

void System_Para_Save(void)
{
	u8 i,k = 0,crc1=0,crc2=0;
	
	k=0;
	eeprom_buffer[k++] = 0xAA;
	eeprom_buffer[k++] = 0x55;
	eeprom_buffer[k++] = m_para.temp_h;
	eeprom_buffer[k++] = m_para.temp_l;
	eeprom_buffer[k++] = m_para.rhum_h;
	eeprom_buffer[k++] = m_para.rhum_l;
	eeprom_buffer[k++] = m_para.o3_tim_m;
	eeprom_buffer[k++] = m_para.o3_tim_s;
	for(i=0;i<EEPROM_LEN_MAX-2;i++)
	{
		crc1 += eeprom_buffer[i];
	}
	eeprom_buffer[EEPROM_LEN_MAX-2] = crc1;
	for(i=0;i<EEPROM_LEN_MAX-1;i++)
	{
		crc2 += eeprom_buffer[i];
	}
	eeprom_buffer[EEPROM_LEN_MAX-1] = crc2;
	eeprom_write(EEPROM_ADDR,EEPROM_LEN_MAX,eeprom_buffer);
}

void System_Para_Get(void)
{
	u8 i,k = 0,crc1=0,crc2=0,err=0;
	
	eeprom_read(EEPROM_ADDR,EEPROM_LEN_MAX,eeprom_buffer);
	k = 0;
	if(eeprom_buffer[k++] != 0xAA)err = 1;
	if(err==0)
	{
		if(eeprom_buffer[k++] != 0x55)err = 1;
	}
	if(err==0)
	{
		for(i=0;i<EEPROM_LEN_MAX-2;i++)
		{
			crc1 += eeprom_buffer[i];
		}
		if(crc1 != eeprom_buffer[EEPROM_LEN_MAX-2])err = 1;
	}
	
	if(err==0)
	{
		for(i=0;i<EEPROM_LEN_MAX-1;i++)
		{
			crc2 += eeprom_buffer[i];
		}
		if(crc2 != eeprom_buffer[EEPROM_LEN_MAX-1])err = 1;
	}
	if(err==1)
	{
		System_Para_Save();
	}
	else
	{
		k = 2;
		m_para.temp_h = eeprom_buffer[k++];
		m_para.temp_l = eeprom_buffer[k++];
		m_para.rhum_h = eeprom_buffer[k++];
		m_para.rhum_l = eeprom_buffer[k++];
		m_para.o3_tim_m = eeprom_buffer[k++];
		m_para.o3_tim_s = eeprom_buffer[k++];
	}
}

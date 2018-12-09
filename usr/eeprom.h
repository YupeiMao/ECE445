typedef bit BOOL;
typedef unsigned char BYTE;
typedef unsigned int WORD;

#define ERROR   0
#define OK      1

//-----------------------------------------------


sfr IAP_DATA    =   0xC2;           //IAP���ݼĴ���
sfr IAP_ADDRH   =   0xC3;           //IAP��ַ�Ĵ������ֽ�
sfr IAP_ADDRL   =   0xC4;           //IAP��ַ�Ĵ������ֽ�
sfr IAP_CMD     =   0xC5;           //IAP����Ĵ���
sfr IAP_TRIG    =   0xC6;           //IAP������Ĵ���
sfr IAP_CONTR   =   0xC7;           //IAP���ƼĴ���


#define CMD_IDLE    0               //����ģʽ
#define CMD_READ    1               //IAP�ֽڶ�����
#define CMD_PROGRAM 2               //IAP�ֽڱ������
#define CMD_ERASE   3               //IAP������������

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
�ر�IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //�ر�IAP����
    IAP_CMD = 0;                    //�������Ĵ���
    IAP_TRIG = 0;                   //��������Ĵ���
    IAP_ADDRH = 0x80;               //����ַ���õ���IAP����
    IAP_ADDRL = 0;
}

/*----------------------------
��ISP/IAP/EEPROM�����ȡһ�ֽ�
----------------------------*/
BYTE IapReadByte(WORD addr)
{
    BYTE dat;                       //���ݻ�����

    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_READ;             //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    dat = IAP_DATA;                 //��ISP/IAP/EEPROM����
    IapIdle();                      //�ر�IAP����

    return dat;                     //����
}

/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(WORD addr, BYTE dat)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_PROGRAM;          //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_DATA = dat;                 //дISP/IAP/EEPROM����
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}

/*----------------------------
��������
----------------------------*/
void IapEraseSector(WORD addr)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_ERASE;            //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}

BYTE eeprom_read(WORD begin_addr, WORD counter, BYTE array[])
{
    WORD i = 0;
    WORD in_sector_begin_addr = 0;
    WORD sector_addr = 0;
    WORD byte_addr = 0;

    /* ���Ƿ�����Ч��Χ,�˺������������������ */
    if(counter > EEPROM_LEN_MAX)
        return ERROR;
    in_sector_begin_addr = begin_addr & 0x01ff;
    /* �ٶ��������ĵ�0���ֽڿ�ʼ����USED_BYTE_QTY_IN_ONE_SECTOR-1���ֽڽ���,���沿�ֲ���,�����ױ�д */
    if((in_sector_begin_addr + counter) > EEPROM_LEN_MAX)
        return ERROR;

    /* ������������ 0 - (USED_BYTE_QTY_IN_ONE_SECTOR-1) �ֽ����ݶ��뻺�������� */
    sector_addr = (begin_addr & 0xfe00);
    byte_addr = sector_addr;

    for(i = 0; i < counter; i++)
    {
        array[i] = IapReadByte(byte_addr++);
    }
    return  OK;
}

/* д���ݽ� ����Flash�洢��, ֻ��ͬһ��������д��������ԭ������ */
/* begin_addr,��д����Flash��ʼ��ַ��counter,����д���ٸ��ֽڣ� array[]��������Դ   */
BYTE eeprom_write(WORD begin_addr, WORD counter, BYTE array[])
{
    WORD i = 0;
    WORD in_sector_begin_addr = 0;
    WORD sector_addr = 0;

    /* ���Ƿ�����Ч��Χ,�˺������������������ */
    if(counter > EEPROM_LEN_MAX)
        return  ERROR;
    in_sector_begin_addr = begin_addr & 0x01ff;
    if((in_sector_begin_addr + counter) > EEPROM_LEN_MAX)
        return ERROR;

    /* ���� Ҫ�޸�/д�� ������ */
    IapEraseSector(begin_addr);

    for(i=0; i<counter; i++)
    {
        /* дһ���ֽ� */
        IapProgramByte(begin_addr, array[i]);
        /*  �Ƚ϶Դ� */
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

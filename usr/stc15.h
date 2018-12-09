#ifndef __STC15_H__
#define __STC15_H__

//P0M1   |        0            |     		0   					|    1     |      1
//P0M0   |        0            |        1             |    0     |      1
//       |׼˫��I/O��(������)   | �������(ǿ�������)  | �������� |   ��©���
sfr P0M1 = 0x93;
sfr P0M0 = 0x94;
sfr P1M1 = 0x91;
sfr P1M0 = 0x92;
sfr P2M1 = 0x95;
sfr P2M0 = 0x96;
sfr P3M1 = 0xb1;
sfr P3M0 = 0xb2;
sfr P4M1 = 0xb3;
sfr P4M0 = 0xb4;
sfr P5M1 = 0xC9;
sfr P5M0 = 0xCA;
sfr P6M1 = 0xCB;
sfr P6M0 = 0xCC;
sfr P7M1 = 0xE1;
sfr P7M0 = 0xE2;

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;
sbit P10 = P1^0;
sbit P11 = P1^1;
sbit P12 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit P17 = P1^7;
sbit P20 = P2^0;
sbit P21 = P2^1;
sbit P22 = P2^2;
sbit P23 = P2^3;
sbit P24 = P2^4;
sbit P25 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;
sbit P30 = P3^0;
sbit P31 = P3^1;
sbit P32 = P3^2;
sbit P33 = P3^3;
sbit P34 = P3^4;
sbit P35 = P3^5;
sbit P36 = P3^6;
sbit P37 = P3^7;

sfr P4   = 0xC0;
sbit P40 = P4^0;
sbit P41 = P4^1;
sbit P42 = P4^2;
sbit P43 = P4^3;
sbit P44 = P4^4;
sbit P45 = P4^5;
sbit P46 = P4^6;
sbit P47 = P4^7;

sfr P5   = 0xC8;
sbit P50 = P5^0;
sbit P51 = P5^1;
sbit P52 = P5^2;
sbit P53 = P5^3;
sbit P54 = P5^4;
sbit P55 = P5^5;
sbit P56 = P5^6;
sbit P57 = P5^7;

sfr P6   = 0xE8;
sbit P60 = P6^0;
sbit P61 = P6^1;
sbit P62 = P6^2;
sbit P63 = P6^3;
sbit P64 = P6^4;
sbit P65 = P6^5;
sbit P66 = P6^6;
sbit P67 = P6^7;

sfr P7   = 0xF8;
sbit P70 = P7^0;
sbit P71 = P7^1;
sbit P72 = P7^2;
sbit P73 = P7^3;
sbit P74 = P7^4;
sbit P75 = P7^5;
sbit P76 = P7^6;
sbit P77 = P7^7;

sfr AUXR  = 0x8e;               //�����Ĵ���
sfr IE2     = 0xAF;                 //�ж�ʹ�ܼĴ���2

sfr P_SW1   = 0xA2;             //���蹦���л��Ĵ���1
sfr P_SW2   = 0xBA;             //���蹦���л��Ĵ���2

sfr S2CON = 0x9a;               //UART2 ���ƼĴ���
sfr S2BUF = 0x9b;               //UART2 ���ݼĴ���

sfr S3CON = 0xac;               //UART3 ���ƼĴ���
sfr S3BUF = 0xad;               //UART3 ���ݼĴ���

sfr T2H   = 0xd6;               //��ʱ��2��8λ
sfr T2L   = 0xd7;               //��ʱ��2��8λ

sfr T3H     = 0xD4;             //��ʱ��3��8λ
sfr T3L     = 0xD5;             //��ʱ��3��8λ

sfr T4T3M   = 0xD1;             //��ʱ��3�Ͷ�ʱ��4���ƼĴ���
sfr T4H     = 0xD2;             //��ʱ��4��8λ
sfr T4L     = 0xD3;             //��ʱ��4��8λ

sfr ADC_CONTR   =   0xBC;           //ADC���ƼĴ���
sfr ADC_RES     =   0xBD;           //ADC��8λ���
sfr ADC_LOW2    =   0xBE;           //ADC��2λ���
sfr P1ASF       =   0x9D;           //P1�ڵ�2���ܿ��ƼĴ���

#endif



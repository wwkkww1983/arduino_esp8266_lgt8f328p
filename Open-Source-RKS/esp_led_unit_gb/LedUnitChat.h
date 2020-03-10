#include "hzk16.h"
#include "UnicodeGbkMap.h"

/***********************************************xyz
ASCII纵向取模8*16字库。为1亮。
横向取模（8位）(取完一横后再取下一横)-LCD12864SPI
每个字节代表一列8个像素值，每个ASCII由8*16/8=16个字节存储，前8个字节为上半部分值，后8个字节为下半部分值。
共95个，从32(空格)到126。ASCII816[0]为空格。
ASCII值减32即为数组二维下标。
**************************************************/
const unsigned char PROGMEM  ASCII816[96][16]=
{
	 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x18,0x18,0x00,0x00
	,0x00,0x12,0x36,0x24,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x24,0x24,0x24,0xFE,0x48,0x48,0x48,0xFE,0x48,0x48,0x48,0x00,0x00
	,0x00,0x00,0x10,0x38,0x54,0x54,0x50,0x30,0x18,0x14,0x14,0x54,0x54,0x38,0x10,0x10
	,0x00,0x00,0x00,0x44,0xA4,0xA8,0xA8,0xA8,0x54,0x1A,0x2A,0x2A,0x2A,0x44,0x00,0x00
	,0x00,0x00,0x00,0x30,0x48,0x48,0x48,0x50,0x6E,0xA4,0x94,0x88,0x89,0x76,0x00,0x00
	,0x00,0x60,0x60,0x20,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	,0x00,0x02,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04,0x02,0x00
	,0x00,0x40,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20,0x40,0x00
	,0x00,0x00,0x00,0x00,0x10,0x10,0xD6,0x38,0x38,0xD6,0x10,0x10,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x10,0x00,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x20,0xC0
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00
	,0x00,0x00,0x01,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x00
	,0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00
	,0x00,0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00
	,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x04,0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00
	,0x00,0x00,0x00,0x3C,0x42,0x42,0x04,0x18,0x04,0x02,0x02,0x42,0x44,0x38,0x00,0x00
	,0x00,0x00,0x00,0x04,0x0C,0x14,0x24,0x24,0x44,0x44,0x7E,0x04,0x04,0x1E,0x00,0x00
	,0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x58,0x64,0x02,0x02,0x42,0x44,0x38,0x00,0x00
	,0x00,0x00,0x00,0x1C,0x24,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x24,0x18,0x00,0x00
	,0x00,0x00,0x00,0x7E,0x44,0x44,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00
	,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00
	,0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x26,0x1A,0x02,0x02,0x24,0x38,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00,0x00,0x18,0x18,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x20
	,0x00,0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x40,0x20,0x10,0x08,0x04,0x02,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0xFE,0x00,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x02,0x04,0x08,0x10,0x20,0x40,0x00,0x00
	,0x00,0x00,0x00,0x3C,0x42,0x42,0x62,0x02,0x04,0x08,0x08,0x00,0x18,0x18,0x00,0x00
	,0x00,0x00,0x00,0x38,0x44,0x5A,0xAA,0xAA,0xAA,0xAA,0xB4,0x42,0x44,0x38,0x00,0x00
	,0x00,0x00,0x00,0x10,0x10,0x18,0x28,0x28,0x24,0x3C,0x44,0x42,0x42,0xE7,0x00,0x00
	,0x00,0x00,0x00,0xF8,0x44,0x44,0x44,0x78,0x44,0x42,0x42,0x42,0x44,0xF8,0x00,0x00
	,0x00,0x00,0x00,0x3E,0x42,0x42,0x80,0x80,0x80,0x80,0x80,0x42,0x44,0x38,0x00,0x00
	,0x00,0x00,0x00,0xF8,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0xF8,0x00,0x00
	,0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x42,0x42,0xFC,0x00,0x00
	,0x00,0x00,0x00,0xFC,0x42,0x48,0x48,0x78,0x48,0x48,0x40,0x40,0x40,0xE0,0x00,0x00
	,0x00,0x00,0x00,0x3C,0x44,0x44,0x80,0x80,0x80,0x8E,0x84,0x44,0x44,0x38,0x00,0x00
	,0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00
	,0x00,0x00,0x00,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00
	,0x00,0x00,0x00,0x3E,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x88,0xF0
	,0x00,0x00,0x00,0xEE,0x44,0x48,0x50,0x70,0x50,0x48,0x48,0x44,0x44,0xEE,0x00,0x00
	,0x00,0x00,0x00,0xE0,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x42,0xFE,0x00,0x00
	,0x00,0x00,0x00,0xEE,0x6C,0x6C,0x6C,0x6C,0x54,0x54,0x54,0x54,0x54,0xD6,0x00,0x00
	,0x00,0x00,0x00,0xC7,0x62,0x62,0x52,0x52,0x4A,0x4A,0x4A,0x46,0x46,0xE2,0x00,0x00
	,0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0x82,0x82,0x44,0x38,0x00,0x00
	,0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0xE0,0x00,0x00
	,0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x82,0x82,0x82,0xB2,0xCA,0x4C,0x38,0x06,0x00
	,0x00,0x00,0x00,0xFC,0x42,0x42,0x42,0x7C,0x48,0x48,0x44,0x44,0x42,0xE3,0x00,0x00
	,0x00,0x00,0x00,0x3E,0x42,0x42,0x40,0x20,0x18,0x04,0x02,0x42,0x42,0x7C,0x00,0x00
	,0x00,0x00,0x00,0xFE,0x92,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00
	,0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00
	,0x00,0x00,0x00,0xE7,0x42,0x42,0x44,0x24,0x24,0x28,0x28,0x18,0x10,0x10,0x00,0x00
	,0x00,0x00,0x00,0xD6,0x92,0x92,0x92,0x92,0xAA,0xAA,0x6C,0x44,0x44,0x44,0x00,0x00
	,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x18,0x18,0x18,0x24,0x24,0x42,0xE7,0x00,0x00
	,0x00,0x00,0x00,0xEE,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x38,0x00,0x00
	,0x00,0x00,0x00,0x7E,0x84,0x04,0x08,0x08,0x10,0x20,0x20,0x42,0x42,0xFC,0x00,0x00
	,0x00,0x1E,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1E,0x00
	,0x00,0x00,0x40,0x40,0x20,0x20,0x10,0x10,0x10,0x08,0x08,0x04,0x04,0x04,0x02,0x02
	,0x00,0x78,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x78,0x00
	,0x00,0x1C,0x22,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF
	,0x00,0x60,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x1E,0x22,0x42,0x42,0x3F,0x00,0x00
	,0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x64,0x58,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1C,0x22,0x40,0x40,0x40,0x22,0x1C,0x00,0x00
	,0x00,0x00,0x00,0x06,0x02,0x02,0x02,0x1E,0x22,0x42,0x42,0x42,0x26,0x1B,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x7E,0x40,0x40,0x42,0x3C,0x00,0x00
	,0x00,0x00,0x00,0x0F,0x11,0x10,0x10,0x7E,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x44,0x44,0x38,0x40,0x3C,0x42,0x42,0x3C
	,0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00
	,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00
	,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x1C,0x04,0x04,0x04,0x04,0x04,0x04,0x44,0x78
	,0x00,0x00,0x00,0xC0,0x40,0x40,0x40,0x4E,0x48,0x50,0x68,0x48,0x44,0xEE,0x00,0x00
	,0x00,0x00,0x00,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x49,0x49,0x49,0x49,0x49,0xED,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDC,0x62,0x42,0x42,0x42,0x42,0xE7,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD8,0x64,0x42,0x42,0x42,0x44,0x78,0x40,0xE0
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1E,0x22,0x42,0x42,0x42,0x22,0x1E,0x02,0x07
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xEE,0x32,0x20,0x20,0x20,0x20,0xF8,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x40,0x3C,0x02,0x42,0x7C,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x0C,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x28,0x10,0x10,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD7,0x92,0x92,0xAA,0xAA,0x44,0x44,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x6E,0x24,0x18,0x18,0x18,0x24,0x76,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE7,0x42,0x24,0x24,0x28,0x18,0x10,0x10,0xE0
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7E,0x44,0x08,0x10,0x10,0x22,0x7E,0x00,0x00
	,0x00,0x03,0x04,0x04,0x04,0x04,0x04,0x08,0x04,0x04,0x04,0x04,0x04,0x04,0x03,0x00
	,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08
	,0x00,0x60,0x10,0x10,0x10,0x10,0x10,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x60,0x00
	,0x30,0x4C,0x43,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
	,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

//void Hdot()
//{
//	//字库取模改成横向
//	unsigned char ASCII816Buf[16];
//	unsigned char pix = 0;
//	for (int k=0; k<96; k++)
//	{
//		for (int i=0; i<16; i++)//暂存
//		{
//			ASCII816Buf[i]=ASCII816[k][i];
//		}
//
//		for(int j=0; j<8; j++)//转换上半部分8*8
//		{
//			pix = 0;
//			for(int i=0; i<8; i++)
//			{
//				pix = pix<<1;
//				pix=pix+((ASCII816Buf[7-i]>>j)&1);
//			}
//			ASCII816[k][j] = pix;
//		}
//
//		for(int j=8; j<16; j++)//转换下半部分8*8
//		{
//			pix = 0;
//			for(int i=8; i<16; i++)
//			{
//				pix = pix<<1;
//				pix=pix+((ASCII816Buf[16+7-i]>>(j-8))&1);
//			}
//			ASCII816[k][j] = pix;
//		}
//	}
//}


void GetGbk(unsigned short Unicode, unsigned char* GbkA, unsigned char* GbkB)
{
	unsigned long Index;
	//0xFF01～0xFF5E  	//UnicodeGbkMapPunctuation
	//0X4E00～ 0X9FA0   	//UnicodeGbkMap

	if ((Unicode > 0X4E00-1) && (Unicode < 0X9FA0+1))
	{
		Index = (Unicode - 0x4E00) * 2;
		*GbkA = pgm_read_byte(UnicodeGbkMap + Index);//UnicodeGbkMap[Index];
		*GbkB = pgm_read_byte(UnicodeGbkMap + Index +1);//UnicodeGbkMap[Index + 1];
	}
	else if((Unicode > (0xFF01-1)) && (Unicode < (0xFF5F)))
	{
		Index = (Unicode - 0xFF01) * 2;
		*GbkA = pgm_read_byte(UnicodeGbkMapPunctuation + Index);//UnicodeGbkMapPunctuation[Index];
		*GbkB = pgm_read_byte(UnicodeGbkMapPunctuation + Index +1);//UnicodeGbkMapPunctuation[Index + 1];
	}
	else
	{
		*GbkA = 0xA1;
		*GbkB = 0xA1;
	}







}

unsigned short GetUnicode(char* utf8)
{
	unsigned short unicode;
	unicode = (utf8[0] & 0x1F) << 12;
	unicode |= (utf8[1] & 0x3F) << 6;
	unicode |= (utf8[2] & 0x3F);
	return unicode;
}


unsigned char swap(unsigned char pData)
{
	unsigned char value = 0, tmp = 0;

	unsigned char ii, jj;
	for (ii = 0x80, jj = 0; ii != 0; ii = ii >> 1, jj++)
	{
		if (pData & ii) tmp = 1;
		else tmp = 0;
		value |= tmp << jj;
	}

	return value;
}


unsigned long GetOffsetChart(char* OneChart)
{
	unsigned short unicode;
	unicode = GetUnicode(OneChart);

	printf("unicode =  0x%4X\r\n", unicode);

	unsigned char GbkA;
	unsigned char GbkB;
	GetGbk(unicode, &GbkA, &GbkB);

	printf("Gbk  = 0x%2X%2X\r\n", GbkA, GbkB);

	//if ((GbArray[0]-0xA0 > 0) && (GbArray[0] - 0xA0 < 94))
	unsigned long OffsetChart;
	OffsetChart = (94 * (GbkA - 1 - 0xa0) + (GbkB - 1 - 0xa0));

	printf("OffsetChart =   %u\r\n", OffsetChart);

	if (OffsetChart > (267616 / 32))
	{
		return 0;
	}

	return OffsetChart;

	//ShowChineseOnLedUnit(x,y,OffsetChart,&buf[0][32]);

}


void ShowAcsiiOnLedUnit(unsigned char x, unsigned char y, char* OneChart, unsigned char buf[][32])
{

	unsigned char OneASCII816[16];
	//read 16 byte from flash
	memcpy_P(OneASCII816, ASCII816 + OneChart[0]-0x20, 16);

	printf("OneChart[0] = %d \r\n",OneChart[0]-0x20);
	for (int i = (y * 16); i < (y * 16 + 16); i++)
	{
		buf[x][i] = OneASCII816[i%16];
		//buf[x][i] = ASCII816[OneChart[0]-0x20][i%16];
		//buf[x][i] = 0xff;
		//printf("buf[x][i] = 0x%02X \r\n",buf[x][i]);
	}

}




void ShowChineseOnLedUnit(unsigned char x, unsigned char y, char* OneChart, unsigned char buf[][32])
{
	//unsigned char One16Chart[32];
	//memcpy(One16Chart,hzk16+32*Index,32);

	unsigned char OneByte;
	unsigned char AnotherByte;
	unsigned char OneHzk16[32];

	long OffsetChart = GetOffsetChart(OneChart);

	//read 32 byte from flash
	memcpy_P(OneHzk16, hzk16 + OffsetChart*32, 32);
	

	for (int j = x; j < (x + 2); j++)
	{
		for (int i = (y * 16); i < (y * 16 + 16); i++)
		{
			//buf[j][i] = swap(hzk16[(i%16)*2+j%2+Index*32]);
			if (x%2 == 1)
			{
				/*buf[j][i] = hzk16[(i % 16) * 2 + 1-(j % 2) + OffsetChart * 32];*/
				buf[j][i] = OneHzk16[(i % 16) * 2 + 1-(j % 2)];
			}
			else
			{
				/*buf[j][i] = hzk16[(i % 16) * 2 + j % 2 + OffsetChart * 32];*/
				buf[j][i] = OneHzk16[(i % 16) * 2 + j % 2];
			}

		}
	}
}

void ShowStringOnLedUnit(char* String, unsigned char buf[][32])
{

	static int ChartPostion = 0;
	int RowPostion = 0;
	int LinePostion = 0;

	while (1)
	{
		//sleep(1);

		printf("ChartPostion = %d  strlen(String) = %d\r\n",ChartPostion,strlen(String));
		if (ChartPostion >= strlen(String))
		{
			while (1)
			{
				if (RowPostion > 7)
				{
					if (LinePostion == 0)
					{
						LinePostion++;
						RowPostion = 0;
					}
					else
					{
						ChartPostion = 0;
						return;
					}

				}
				ShowAcsiiOnLedUnit(RowPostion,LinePostion," ",buf);
				ChartPostion++;
				RowPostion++;
			}
			//ChartPostion = 0;
			//return;
		}

		if ((String[ChartPostion] > (0x20 - 1)) && (String[ChartPostion] < (0x7F + 1)))
		{
			if (RowPostion > 7)
			{
				if (LinePostion == 0)
				{
					LinePostion++;
					RowPostion = 0;
				}
				else
				{
					ChartPostion = 0;
					return;
				}

			}
			ShowAcsiiOnLedUnit(RowPostion,LinePostion,String+ChartPostion,buf);
			ChartPostion++;
			RowPostion++;
		}
		else if ((String[ChartPostion]&0xF0)  == 0xE0)
		{
			if (RowPostion > 6)
			{
				ShowAcsiiOnLedUnit(RowPostion,LinePostion," ",buf);
				if (LinePostion == 0)
				{
					LinePostion++;
					RowPostion = 0;
				}
				else
				{
					ChartPostion = 0;
					return;
				}
			}
			ShowChineseOnLedUnit(RowPostion,LinePostion,String+ChartPostion,buf);
			ChartPostion = ChartPostion+3;
			RowPostion = RowPostion+2;
		}
	}

}



#define NON_NUM '0'

int hex2num(char c)
{
	if (c>='0' && c<='9') return c - '0';
	if (c>='a' && c<='z') return c - 'a' + 10;//这里+10的原因是:比如16进制的a值为10
	if (c>='A' && c<='Z') return c - 'A' + 10;

	printf("unexpected char: %c", c);
	return NON_NUM;
}


int URLDecode(const char* str, const int strSize, char* result, const int resultSize)
{
	char ch,ch1,ch2;
	int i;
	int j = 0;//record result index

	if ((str==NULL) || (result==NULL) || (strSize<=0) || (resultSize<=0)) {
		return 0;
	}

	for ( i=0; (i<strSize) && (j<resultSize); ++i) {
		ch = str[i];
		switch (ch) {
			case '+':
				result[j++] = ' ';
				break;
			case '%':
				if (i+2<strSize) {
					ch1 = hex2num(str[i+1]);//高4位
					ch2 = hex2num(str[i+2]);//低4位
					if ((ch1!=NON_NUM) && (ch2!=NON_NUM))
						result[j++] = (char)((ch1<<4) | ch2);
					i += 2;
					break;
				} else {
					break;
				}
			default:
				result[j++] = ch;
				break;
		}
	}

	result[j] = 0;
	return j;
}



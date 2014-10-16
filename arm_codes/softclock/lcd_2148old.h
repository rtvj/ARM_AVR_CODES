/****************************************************************
Name		: lcd_2148.c
Description	: Library for JHD162A (HD44780) on lpc2148
date modified :	7th Apr 2010
Author		: Aditya
*****************************************************************/

#include"LPC214x.h"
 

#define LINE1	0x80
#define LINE2	0xC0

#define LCD_EN   22
#define LCD_RS   24
#define LCD_RW   23

void delay(unsigned int i)
{
	volatile unsigned int j=0,k = 0;
	for (j=0;j<i;j++)
		for (k=0;k<6000;k++);	// 
}

void latch(void)
{

	delay(10);
	IOSET1 |= (1 << LCD_EN);	// LCD_EN = 1
	delay(10);
	IOCLR1 |= (1 << LCD_EN);
}

void lcd2148_cmd(unsigned char cmd)
{
	IOCLR1 |= (1 << LCD_RS);		// RS = 0, command

	IOCLR0 |= (0x0f << 10);
	IOSET0 |= ((cmd & 0xf0) << 6);	// write higher nibble first
	latch();

	IOCLR0 |= (0x0f << 10);
	IOSET0 |= ((cmd & 0x0f) << 10);	// write lower nibble
	latch();
}

void lcd_gotoxy1(unsigned char pos)
{
	lcd2148_cmd(LINE1+pos);
}

void lcd_gotoxy2(unsigned char pos)
{
	lcd2148_cmd(LINE2+pos);
}



void lcd2148_data(unsigned char data)
{
	IOSET1 |= (1 << LCD_RS);		// RS = 1, data

	IOCLR0 |= (0x0f << 10);
	IOSET0 |= ((data & 0xf0) << 6);	// write higher nibble first
	latch();

	IOCLR0 |= (0x0f << 10);
	IOSET0 |= ((data & 0x0f) << 10);	// write lower nibble
	latch();
}

void lcd2148_init(void)
{	 /* D7-D4 : P0.13-P0.10 
		EN_LCD P1.22
		R/W_LCD P1.23
		RS_LCD P1.24  */
	PINSEL0 &= ~(0xff << 20);
	PINSEL2 &= ~(1 << 3);
	IODIR0 |= (0xf << 10);		// data outputs
	IODIR1 |= (7 << 22);		// control outputs
	IOCLR0 |= 0x00003c00;		// clearing port pins

	IOCLR1 |= (1 << LCD_EN)|(1 << LCD_RW)|(1 << LCD_RS);	// select RS=0 i.e. command mode, R/W = 0, EN =0
	delay(100);
	IOCLR0 |= (0xf << 10);
	IOSET0 |= (3 << 10);		// cmd(0x30)
	latch();					// LCD_EN pulse

	delay(5);
	IOCLR0 |= (0xf << 10);
	IOSET0 |= (3 << 10);		// cmd(0x30)
	latch();					// LCD_EN pulse

	delay(1);
	IOCLR0 |= (0xf << 10);
	IOSET0 |= (3 << 10);		// cmd(0x30)
	latch();					// LCD_EN pulse

	IOCLR0 |= (0xf << 10);
	IOSET0 |= (2 << 10);		// cmd(0x20), 4-bit mode
	latch();					// LCD_EN pulse
  
	lcd2148_cmd(0x28);			// 2 line display, 5x8 display
	lcd2148_cmd(0x0f);			// display ON, cursor ON, blink ON
	lcd2148_cmd(0x01);			// clear display
	lcd2148_cmd(0x02);			// cursor home
	lcd2148_cmd(0x06);			// increment cursor by 1, no shift

}
/*
void lcd_string(unsigned char str[32])
{
	unsigned char k=0;
	PORTUSED=0x01;
	CLEARBIT(PORTUSED,BIT(0)+BIT(2));
	while(str[k]!='\0')	//Till null character is encountered
		{
			if(k==16)
				lcd_cmd(LINE2);
			PORTUSED=((str[k])&0xF0)|0x01;
			toggleE();
			PORTUSED=((str[k]&(0x0F))*16)|0x01;
			toggleE();
			k++;
		}
}
*/

void lcd_showvalue(unsigned char num)	
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));
	
//	lcd2148_data(H+48);
	lcd2148_data(T+48);
	lcd2148_data(O+48);
}


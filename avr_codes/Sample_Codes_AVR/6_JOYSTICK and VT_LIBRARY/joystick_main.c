/*****************************************************************
FILENAME 	: Joystick_main
Target	 	: ATmega128
Frequency	: 16Mhz
Compiler 	:  avr-gcc
Author   	: TEAM
Description	: This is sample application which uses the joystick
			  as a mouse on serial using VTlibrary
*****************************************************************/
#include<avr/io.h>
#include<avr/interrupt.h>
#include"LCD_mega128.h"
#include"VT102lib.h"

#define JOY_X 0
#define JOY_Y 1

#define JOY_X_MAXCHK 	240
#define JOY_X_MINCHK 	10

#define JOY_Y_MAXCHK 	240
#define JOY_Y_MINCHK 	10
#define SHOW_CURSOR		'*'
#define SHOW_CURSOR_BLANK 	' '


volatile unsigned int G_Joy_SPEED = 1500;

volatile unsigned char G_Joy_xvalue = 100;
volatile unsigned char G_Joy_yvalue = 100;

volatile unsigned char G_Joy_over = 0;


void clearscreen(unsigned char X,unsigned char Y);

int main(void)
{
	unsigned char s_x=40,s_y=10;

	UART_config(9600);
	lcd_init();

	/////////////  CONFIGURE ADC  ////////////////////////////////////////////
	ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<ADLAR) |(1<<MUX0);
	ADCSRA = 0xEF;
	/////////////  CONFIGURE EXT INT  ////////////////////////////////////////
	DDRE &= 0xBF;	//configure as input for INT6
	PORTE |=0x80;	//active pullup for INT6
	EICRB=0b11000000;
	EIMSK=0b10000000;
	/////////////////////////////////////////////////////////////////////////


	VT102DispClrScr();
	VT102DispChar(s_x,s_y,SHOW_CURSOR,COLOR_BLACK,COLOR_RED);
	VT102DispChar(s_x,s_y,SHOW_CURSOR_BLANK,COLOR_BLACK,COLOR_RED);
	VT102DispStr(50,24,"SPEED (SW4 on Board) :",COLOR_BLACK,COLOR_RED);
	sei();

	while(1)
	{
		if(G_Joy_over)
		{
			lcd_gotoxy1(0);
			lcd_showvalue(G_Joy_xvalue);
			lcd_gotoxy2(0);
			lcd_showvalue(G_Joy_yvalue);
			G_Joy_over = 0;

			if(G_Joy_xvalue>JOY_X_MAXCHK && s_x>0)
			{
				clearscreen(s_x,s_y);
				VT102DispChar(--s_x,s_y,SHOW_CURSOR,COLOR_BLACK,COLOR_RED);
			}
			else if(G_Joy_xvalue<JOY_X_MINCHK && s_x<=80)
			{
				clearscreen(s_x,s_y);
				VT102DispChar(++s_x,s_y,SHOW_CURSOR,COLOR_BLACK,COLOR_RED);
			}
			else if(G_Joy_yvalue>JOY_Y_MAXCHK && s_y>0)
			{
				clearscreen(s_x,s_y);
				VT102DispChar(s_x,--s_y,SHOW_CURSOR,COLOR_BLACK,COLOR_RED);
			}
			else if(G_Joy_yvalue<JOY_Y_MINCHK && s_y<25)
			{
				clearscreen(s_x,s_y);
				VT102DispChar(s_x,++s_y,SHOW_CURSOR,COLOR_BLACK,COLOR_RED);
			}
		}
	}
}

void clearscreen(unsigned char X,unsigned char Y)
{
	cli();
	VT102DispChar(X,Y,SHOW_CURSOR_BLANK,COLOR_BLACK,COLOR_RED);
	sei();
	/* VT102DispClrScr(); */
}

ISR(ADC_vect)
{
	static unsigned char JOY_scan = JOY_X;
	static unsigned char Joy_value = 0;
	static int count=0;

	Joy_value = ADCH;
	count++;

	if(count == G_Joy_SPEED)
	{
		count=0;

		if(JOY_scan == JOY_X)
		{
			JOY_scan = JOY_Y;

			G_Joy_xvalue = Joy_value;

			ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<ADLAR) |(1<<MUX1);
		}
		else
		{
			JOY_scan = JOY_X;

			G_Joy_yvalue = Joy_value;

			ADMUX = (1<<REFS1) | (1<<REFS0) | (1<<ADLAR) |(1<<MUX0);
		}
		G_Joy_over = 1;
	}
}

ISR(INT7_vect)
{
	char Mystring[10];
	if(G_Joy_SPEED>300)
	{
		G_Joy_SPEED -=100;
		sprintf(Mystring,"%04d",G_Joy_SPEED);
		VT102DispStr(75,24,Mystring,COLOR_BLACK,COLOR_RED);
	}
}

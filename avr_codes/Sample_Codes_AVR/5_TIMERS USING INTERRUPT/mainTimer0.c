/****************************************************************************************
FileName		:	mainTimer0.c
ProjectName		:	Timer0 TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Author			:	TEAM
Description		:	This is a program for software clock using Timer0.
****************************************************************************************/

#include<avr/io.h>
#include <avr/interrupt.h>

#include "Timer0.h"
#include "Serial.h"

#include "LCD_mega128.h"

unsigned int MSEC_var = 999;
unsigned char SEC_var = 59;
unsigned char MIN_var = 59;
unsigned char HRS_var = 23;
unsigned char Update_flag = 0;

int main(void)
{
	unsigned char Mystring[20];

	Serial_Init();
	
	lcd_init();

	print_string("\nSTART MAIN TIMER TEST");

	Timer0_Init();
	sei();

	while(1)
	{
		if(Update_flag)
		{
			sprintf(Mystring,"%02d %02d %02d",(unsigned char)HRS_var,(unsigned char)MIN_var,(unsigned char)SEC_var);
			print_string("\n\r");
			print_string(Mystring);
			lcd_gotoxy1(0);
			lcd_string(Mystring);
			Update_flag = 0;
		}
	}
}

ISR(TIMER0_OVF_vect)
{
	MSEC_var--;
	if(!MSEC_var)
	{
		MSEC_var = 999;
		SEC_var++;
		Update_flag = 1;
		if(SEC_var > 59)
		{
			SEC_var = 0;
			MIN_var++;
			if(MIN_var > 59)
			{
				HRS_var++;
				MIN_var = 0;
			}
			if(HRS_var > 23)
			{
				HRS_var = 0;
				MIN_var = 0;
				SEC_var = 0;
			}
		}
	}
	Timer0_LoadCount();	//reload count value
}

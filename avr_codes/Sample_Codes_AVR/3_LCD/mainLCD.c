/****************************************************************************************
FileName		:	mainLCD.c
ProjectName		:	LCD TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Author			:	TEAM
Description		:	This is a program to test the LCD.
****************************************************************************************/

#include <avr/io.h>
#include "LCD_mega128.h"

int main(void)
{
	
	lcd_init();
	
	lcd_gotoxy1(0);

	lcd_string("   Soham   ");

	lcd_gotoxy2(0);
	
	lcd_string("   Wadke  ");
	
	while(1);
}

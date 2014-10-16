/****************************************************************************************
FileName		:	mainGPsw.c
ProjectName		:	LED TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Author			:	TEAM
Description		:	This is a program to test the Switches SW2(PD6) and SW1(PD7).
****************************************************************************************/

#include<avr/io.h>

#include "Serial.h"

#define SW_DIR DDRD &= 0x3F

#define EXSW1 PIND & 0x80	/* This is External switche connected on uNiBoard SW1(PD7) */
#define EXSW2 PIND & 0x40	/* This is External switche connected on uNiBoard SW2(PD6) */

int main(void)
{

	Serial_Init();
	print_string("\n\r START MAIN");

	//PORTD = 0x00;
	SW_DIR;

	while(1)
	{
		if(!(EXSW1))	/* check for pin for low */
			print_string("\nSW1 PRESSED");
		if(!(EXSW2))	/* check for pin for low */
			print_string("\nSW2 PRESSED");
	}
}

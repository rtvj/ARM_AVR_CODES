/****************************************************************************************
FileName		:	mainBUZZ.c
ProjectName		:	BUZZER TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Author			:	TEAM
Description		:	This is a program to test the Buzzer on PA3.
****************************************************************************************/

#include<avr/io.h>

#define BUZZER_PA3_DIR	DDRA |= 0x08
#define BUZZER_ON		PORTA |= 0x08
#define BUZZER_OFF		PORTA &= 0xF7

void Buzzer_Init(void)
{
	BUZZER_PA3_DIR;	/* Initializes PA3 as an output pin */
}

int main(void)
{
	volatile unsigned char idelay;
	volatile unsigned int jdelay;

	Buzzer_Init();	/* Buzzer pin as an output */

	BUZZER_ON;

	for(idelay=0;idelay<10;idelay++)	/* Software Delay */
		for(jdelay=0;jdelay<50000;jdelay++);

	//BUZZER_OFF;

	while(1);	/* wait forever */
}

/****************************************************************************************
FileName		:	mainLED.c
ProjectName		:	LED TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Author			:TEAM
Description		:	This is a program shows how to use the general purpose port pin.
					The PORT is set as ouput for testing LED's.
					
					NOTE : Connect FRC cable between PORTC and LED PORT
****************************************************************************************/

#include<avr/io.h>

#define LEDPORTDIR	DDRC	/* set the PORT direction */
#define LEDPORT		PORTC

void LED_Init(void)
{
	LEDPORTDIR = 0xFF;	/* SET Direction of PORT as Output */
	LEDPORT = 0xFF;		/* Turn OFF all the LED */
}

int main(void)
{
	volatile unsigned char idelay;
	volatile unsigned int jdelay;

	LED_Init();	/* Initializes LED as an output port and TURN OFF the LED's*/

	while(1)
	{
		for(idelay=0;idelay<10;idelay++)	/* Software Delay */
			for(jdelay=0;jdelay<60000;jdelay++);
		EEARH |= (1 << 2);
		LEDPORT = LEDPORT ^ 0xFF;	/* Toggle the LED'S */
	}
}

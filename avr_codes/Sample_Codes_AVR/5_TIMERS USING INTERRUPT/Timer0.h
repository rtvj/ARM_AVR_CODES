/****************************************************************************************
FileName		:	Timer0.h
ProjectName		:	Timer0 TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Author			:	TEAM
Description		:	This is a header file for configuring Timer0 on Atmega128.
****************************************************************************************/

#ifndef Timer0_H
	#define Timer0_H
	#define FOSC 16000000// Clock Speed

	void Timer0_Init(void);
	void Timer0_LoadCount(void);

	void Timer0_Init(void)
	{
		/*
		CRYSTAL 	16MHZ
		PRESCALAR	1024
		therefore counter is updated after every 
		16MHZ/1024	= 0.000064 sec(resolution of timer)
		therefore for the timer to overflow at 1msec
		0.000064 * 15 = 0.96 msec ~ 1msec
		the counter reload value = 256 - 15 = 241
		RELOAD count = 0XF0
		*/

		TCCR0 = 0x07;	/* PRESCALAR = CLK/1024, ALL NORMAL OPERATION AND COMPARE OFF */
		TIMSK  = 0x01;	/* T0IE0 Timer0 overflow ISR Enable */
		Timer0_LoadCount();
	}

	void Timer0_LoadCount(void)
	{
		TCNT0 = 241;	/* reload value = 256 - 15 = 241 */
	}
#endif

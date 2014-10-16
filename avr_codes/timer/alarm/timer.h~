#include<avr/io.h>

void timer_init()
{
	TCCR0 = 0X0F;// CTC MODE & FOC/1024 PRESCALAR
	OCR0 = 156;// TO COUNT 156 STEPS (DELAY OF 10 MSEC)
}

void sec_delay()
{	
	for(unsigned char count=100;count>0;count--)
	{
	while(!(TIFR&(1<<OCF0)));// POLL TIMER OVERFLOW FLAG TO SET TO 1 (10 MSEC HAS ELAPSED)
	TIFR|=(1<<OCF0);// CLEAR FLAG BY WRITING 1 TO IT
	
	} 
}

#include<avr/io.h>

void timer_init()
{
	TCCR0 = 0X07;// NORMAL MODE & FOC/1024 PRESCALAR
	TCNT0 = 100;// TO COUNT 156 STEPS (DELAY OF 10 MSEC)
}

void sec_delay()
{	
	for(unsigned char count=100;count>0;count--)
	{
	while(!(TIFR&(1<<TOV0)));// POLL TIMER OVERFLOW FLAG TO SET TO 1 (10 MSEC HAS ELAPSED)
	TIFR|=(1<<TOV0);// CLEAR FLAG BY WRITING 1 TO IT
	TCNT0 = 100 ; // RELOAD TIMER COMPARE REGISTER TO SET DELAY OF 10 MSEC
	} 
}

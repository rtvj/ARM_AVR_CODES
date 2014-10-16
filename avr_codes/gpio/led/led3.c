/*
Title :glowing led's one at a time in both ways
11/03/2012
*/

#include<avr/io.h>
#include<util/delay.h>
int main(void)
{
	int i;
	DDRC = 0XFF;// PORTC AS O/P PORT
	
	
	while(1)
	{
		
		for(i=0;i<=7;i++)
		{
		PORTC = 0xff;// all leds are off
		PORTC&=~(1<<i) ;
		_delay_ms(1000);
		}
		for(i=6;i>=1;i--)
		{
		PORTC = 0xff;// all leds are off
		PORTC&=~(1<<i) ;
		_delay_ms(1000);
		}
}	}

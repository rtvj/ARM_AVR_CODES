/*
Title : Blinking of led's
11/03/2012
*/

#include<avr/io.h>
#include<util/delay.h>
int main(void)
{
	DDRC = 0XFF;// PORTC AS O/P PORT
	
	while(1)
	{
		PORTC = 0x00; // all leds are on
		_delay_ms(1000);

		PORTC = 0xff;// all leds are off
		_delay_ms(1000);
	}
}

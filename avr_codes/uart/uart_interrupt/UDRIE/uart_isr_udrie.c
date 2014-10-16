#include"uart.h"
#include<util/delay.h>
#include<avr/interrupt.h>

/*If UDRE is one, the buffer is empty, and therefore ready to be written. UDRE flag can 
generate a Data Register Empty interrupt.

A Data Register Empty interrupt will be generated only if the UDRIE bit is written to one, 
Global Interrupt Flag is written to one and the UDRE bit in UCSRnA is set */

ISR(USART1_UDRE_vect) //ISR while using UDRE flag
{
      UDR1='Z';             
      //_delay_ms(500);
}



int main(void)
{
    sei();
	uart1_init();
    //uart0_init();
	  
	DDRC = 0XFF;// PORTC AS O/P PORT
	PORTC = 0xff;// all leds are off
	
	while(1)
	{
	PORTC = 0x00; // all leds are on
	_delay_ms(500);
	
	PORTC = 0xff;// all leds are off
	_delay_ms(500);
	}
}
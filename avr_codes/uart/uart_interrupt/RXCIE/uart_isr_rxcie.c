#include"uart.h"
#include<util/delay.h>
#include<avr/interrupt.h>

/*RXC flag bit is set when there are unread data in the receive buffer and cleared 
when the receive buffer is empty (i.e., does not contain any unread data).

The RXC flag can be used to generate a Receive Complete interrupt.

A USART Receive Complete interrupt will be generated only if the RXCIE bit is written to one,
Global Interrupt Flag in SREG is written to one and the RXCn bit in UCSRnA is set. */

ISR(USART1_RX_vect) //ISR while using RXC flag  
{
      //unsigned char ch;
      UDR1=UDR1;//  directluy instead of using 2 statement ch=UDR1;UDR1=ch;
      
	  /*ch=UDR1;
      UDR1=ch;  */ 
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
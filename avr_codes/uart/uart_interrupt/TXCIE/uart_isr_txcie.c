#include<util/delay.h>
#include"uart.h"
#include<avr/interrupt.h>

/*A USART Transmit Complete interrupt will be generated only if the TXCIE bit is written to 
one, the Global Interrupt Flag in SREG is written to one and the TXC bit in UCSRnA is set.

TXC flag bit is set when the entire frame in the Transmit Shift Register has been shifted out 
and there are no new data currently present in the transmit buffer (UDR).*/

ISR(USART1_TX_vect) //ISR while using TXC flag
{
	UDR1='A';
	_delay_ms(500);
}

int main(void)
{
	sei();
	uart1_init() ;
	//uart0_init();
	UDR1='Z';// TO initiate transmission & hence to set TXC flag bit.Then ISR will be generated. 
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

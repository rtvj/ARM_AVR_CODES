#include"uart.h"
#include<util/delay.h>
#include<avr/interrupt.h>
ISR(USART1_RX_vect)
{
	
	unsigned char data;
	data = UDR1;
	UDR1 = data;// To display on own terminal
	UDR0 = data;
}

ISR(USART0_RX_vect)
{
	
	unsigned char ch;
	ch = UDR0;
	UDR1 = ch;
}

int main(void)
{
	
	sei();
	uart1_init() ;
	uart0_init();
	DDRC = 0XFF;// PORTC AS O/P PORT
	while(1)
	{
	
	PORTC = 0x00; // all leds are on
	_delay_ms(1000);

	PORTC = 0xff;// all leds are off
	_delay_ms(1000);
	}
}

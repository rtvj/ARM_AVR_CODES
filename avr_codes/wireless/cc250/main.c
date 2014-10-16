#include"uart1.h"
#include"uart0.h"
#include<avr/interrupt.h>
#include<util/delay.h>
//unsigned char data;
volatile unsigned char ch,data;
ISR(USART1_RX_vect)
{
	
	//unsigned char data;
	data = UDR1;
	UDR1 = data;
	UDR0 = data;
}

ISR(USART0_RX_vect)
{
	
	//unsigned char ch;
	ch = UDR0;
	UDR1 = ch;
}
int main()
{
	
	uart1_init();
	uart0_init();
	DDRC = 0XFF;// PORTC AS O/P PORT
	PORTC = 0xff;// all leds are off
	uart0_tx_num(11);
	_delay_ms(10);
	uart0_tx_num(11);
	_delay_ms(10);
	uart0_tx_num(11);
	_delay_ms(10);
	uart0_tx_char('$');
	_delay_ms(10);
	
	sei();

	while(1)
	{
	if(ch == 'p')
	{	
	PORTC = 0x00; // all leds are on
	//_delay_ms(1000);
	}
	if (ch == 'o')
	{	
	PORTC = 0xff;// all leds are off
	//_delay_ms(1000);
	}
	}
}

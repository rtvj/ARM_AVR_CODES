#include<util/delay.h>
#include"uart1.h"
#include"uart0.h"
#include<avr/interrupt.h>
#define cr 0x0d
#define lf 0x0a
ISR(USART1_RX_vect)
{
	
	unsigned char data;
	data = UDR1;
	UDR1 = data;
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
	_delay_ms(1000);
	uart0_tx_str("LLL");
	_delay_ms(500);
	
	/*uart0_tx_char(cr);
	uart0_tx_char(lf);
	uart0_tx_str("AT+MODE=0");
	uart0_tx_char(cr);
	uart0_tx_char(lf);

	uart0_tx_char(cr);
	uart0_tx_char(lf);	
	uart0_tx_str("AT+SETUP");
	uart0_tx_char(cr);
	uart0_tx_char(lf);

	uart0_tx_char(cr);
	uart0_tx_char(lf);	
	uart0_tx_str("AT+CON=00:19:A4:02:DF:B9,2");
	uart0_tx_char(cr);
	uart0_tx_char(lf);
	*/
	

	//DDRC = 0XFF;// PORTC AS O/P PORT
	while(1);
	/*{
	
	PORTC = 0x00; // all leds are on
	_delay_ms(1000);

	PORTC = 0xff;// all leds are off
	_delay_ms(1000);
	}*/
}

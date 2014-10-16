#include<avr/io.h>

void uart1_init(void) // INITIALIZATION FUNCTION
{
	UBRR1H = 0;
	UBRR1L = 103; //0X67; BAUDRATE = 9600

	//UCSR1C = 0X06;// frame : 8 bit data , no parity , stop bit
	UCSR1C |= (1<<UCSZ1) | (1<<UCSZ0);

	UCSR1B |= (1<<TXCIE) | (1<<RXEN) | (1<<TXEN);// ENABLE Transmit ENABLE INTRRRUPT & TRANSMITTER & RECEIVER 
}

void uart0_init(void) // INITIALIZATION FUNCTION
{
	UBRR0H = 0;
	UBRR0L = 103; //0X67; BAUDRATE = 9600

	//UCSR0C = 0X06;// frame : 8 bit data , no parity , stop bit
	UCSR0C |= (1<<UCSZ1) | (1<<UCSZ0);

	UCSR0B |= (1<<TXCIE) | (1<<RXEN) | (1<<TXEN);// ENABLE Transmit ENABLE INTRRRUPT & TRANSMITTER & RECEIVER 
}
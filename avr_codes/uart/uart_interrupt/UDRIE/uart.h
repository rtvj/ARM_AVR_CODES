#include<avr/io.h>

void uart1_init(void) // Initialisation function for uart1
{
	UBRR1H = 0;
	UBRR1L = 103; //0X67; BAUDRATE = 9600

	UCSR1C |= (1<<UCSZ1) | (1<<UCSZ0);// frame : 8 bit data , no parity ,1 stop bit

	//UCSR1B |= (1<<RXEN) | (1<<TXEN) | (1<<RXCIE);// ENABLE RECIEVE INTRRRUPT (while using RXC flag)
	                                               // ENABLE TRANSMITTER & RECEIVE
	UCSR1B |=(1<<RXEN)|(1<<TXEN) |(1<<UDRIE) ;    //while using UDRE flag
	
	//UCSR1B|=(1<<RXEN)|(1<<TXEN)|(1<<TXCIE);         //while using TXC flag

}

void uart0_init(void) // Initialisation function for uart0
{
	UBRR0H = 0;
	UBRR0L = 103; //0X67; BAUDRATE = 9600
	
	UCSR0C |= (1<<UCSZ1) | (1<<UCSZ0);//frame:8 bit data,no parity, 1 stop bit

	UCSR0B |= (1<<RXEN) | (1<<TXEN) | (1<<RXCIE);// ENABLE RECIEVE INTRRRUPT, TRANSMITTER & RECEIVER.
}

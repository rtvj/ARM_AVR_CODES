/****************************************************************************************
FileName		:	Serial.h
ProjectName		:	UART TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Dated			:	23rd July 2008
Author			:	TRI TEAM
Description		:	This is a header file for using UART1 of ATmega128.
****************************************************************************************/

#ifndef Serial_H
	#define Serial_H

	#define FOSC 16000000	/* CPU Clock Frequency */
	#define BAUD 9600		/* Serial transfer rate (Baudrate) */
	#define MYUBRR FOSC/16/BAUD-1

	void USART_Init( unsigned int ubrr );
	void Serial_Init(void);
	void USART_Transmit( unsigned char data );
	unsigned char USART_Receive( void );
	void print_string(unsigned char *Mystr_ptr);


	void Serial_Init(void)
	{
		USART_Init ( MYUBRR );	/* SET THE BAUD RATE, ENABLE THE TRANSMISSION AND RECEPTION OF SERIAL, SET THE FRAME FORMAT */
	}

	void USART_Init( unsigned int ubrr )
	{
	  UBRR1H = (unsigned char)(ubrr>>8); /* Set baud rate */
	  UBRR1L = (unsigned char)ubrr;

	  UCSR1B = (1<<RXEN)|(1<<TXEN);	/* Enable receiver and transmitter */

	  UCSR1C = (1<<USBS)|(3<<UCSZ0);/* Set frame format: 8data, 2stop bit */
	}

	unsigned char USART_Receive( void )
	{
	  while (!(UCSR1A & (1<<RXC))); /* Wait for data to be received */

	  return UDR1;	/* Get and return received data from buffer */
	}

	void USART_Transmit( unsigned char data )
	{
	  while (!(UCSR1A & (1<<UDRE)));	/* Wait for empty transmit buffer */

	  UDR1 = data;	/* Put data into buffer, sends the data */
	}

	void print_string(unsigned char *Mystr_ptr)
	{
		while((*Mystr_ptr) != '\0')	/* print char from str pointer and point to next location */
				USART_Transmit((*Mystr_ptr++));
	}
#endif


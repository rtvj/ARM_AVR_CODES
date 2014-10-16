/*******************************************************************
TEST ASSIGNMENT

FileName		:	Serial.H
Target			:	ATmega128
Project			:	Serial USART TEST 
Author			:	Hardik Shah
Clock frequency	: 	16Mhz
Dated			:	16th May 2008
Description		:		
*******************************************************************/

#include <avr/io.h>

#define FOSC 16000000// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void Serial_Init(void);
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );
void print_string(unsigned char *Mystr_ptr);

void USART_Init( unsigned int ubrr )
{
  /* Set baud rate */
  UBRR1H = (unsigned char)(ubrr>>8);
  UBRR1L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR1B = (1<<RXEN)|(1<<TXEN);
  /* Set frame format: 8data, 2stop bit */
  UCSR1C = (1<<USBS)|(3<<UCSZ0);
}

unsigned char USART_Receive( void )
{
  /* Wait for data to be received */
  while ( !(UCSR1A & (1<<RXC)) )
       ;
  /* Get and return received data from buffer */
  return UDR1;
}

void USART_Transmit( unsigned char data )
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR1A & (1<<UDRE)) )
       ;
  /* Put data into buffer, sends the data */
  UDR1 = data;
}

void print_string(unsigned char *Mystr_ptr)
{
//tested OK
	while((*Mystr_ptr) != '\0')
			USART_Transmit((*Mystr_ptr++)); 	//print char from str pointer and point to next location
}

/*
//tested OK 
void print_string(unsigned char *Mystr_ptr)
{
	while((*Mystr_ptr) != '\0')
		{
			USART_Transmit((*Mystr_ptr)); 	//print char from str pointer
			++Mystr_ptr;					//go to next location
		}
}
*/

void Serial_Init(void)
{
//	SET THE BAUD RATE	
//	ENABLE THE TRANSMISSION AND RECEPTION OF SERIAL
//	SET THE FRAME FORMAT
USART_Init( MYUBRR );
}


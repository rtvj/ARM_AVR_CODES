#ifndef _USART_H
#define _USART_H
#ifndef F_CPU
#define F_CPU 8000000
#endif
#define USART_BAUDRATE 9600
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#include<avr/io.h>
#include<util/delay.h>

void usart_init();
void usart_putch(unsigned char send);
unsigned int usart_getch();

void usart_init()
{
  UCSRB |= (1 << RXEN) | (1 << TXEN);   
  // Turn on the transmission and reception circuitry
  UCSRC |= (1 << URSEL) | (1<<USBS) | (1 << UCSZ0) | (1 << UCSZ1); 
  // Use 8-bit character sizes
  
  UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value..
  // into the low byte of the UBRR register
  UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value..
  // into the high byte of the UBRR register
}

void usart_putch(unsigned char send)
{
  while ((UCSRA & (1 << UDRE)) == 0); // Do nothing until UDR is ready..
// for more data to be written to it
  UDR = send; // Send the byte 
}

unsigned int usart_getch()
{
  while ((UCSRA & (1 << RXC)) == 0);
  // Do nothing until data have been received and is ready to be read from UDR
  return(UDR); // return the byte
}

#endif

#define rs PA0
#define rw PA1
#define en PA2

#include <avr/io.h>
#include <util/delay.h>


void dis_data(char data_value);
void usart_putch(unsigned char send);
unsigned int usart_getch();

int main ( void )
{
  int i;
  unsigned int c;
  
  //-------- led test -----------//
  DDRD |= 0x80;
  for ( i =0; i < 5; i ++ )
  {
    PORTD = ~PORTD;
    _delay_ms ( 500 );
  }
  //-------- led test -----------//
  
  //----- usart + lcd test -------//
  while ( 1 )
  {
    c = usart_getch();
    usart_putch( ( unsigned char ) c );
    dis_data( ( char ) c );
    
  }
  //----- usart + lcd test -------//
}

void dis_data(char data_value)
{
  char data_value1;
  data_value1=data_value&0xF0;
  PORTA=data_value1;
  PORTA|=(1<<rs);
  PORTA&=~(1<<rw);
  PORTA|=(1<<en);
  _delay_ms(1);
  PORTA&=~(1<<en);
  
  data_value1=((data_value<<4)&0xF0);
  PORTA=data_value1;
  PORTA|=(1<<rs);
  PORTA&=~(1<<rw);
  PORTA|=(1<<en);
  _delay_ms(1);
  PORTA&=~(1<<en);
}

void usart_putch(unsigned char send)
{
  while ((UCSRA & (1 << UDRE)) == 0); // Do nothing until UDR is ready..
	// for more data to be written to it
  UDR = send; // Send the byte 
}

unsigned int usart_getch()
{
  while ((UCSRA & (1 << RXC)) == 0);
  // Do nothing until data have been received and is ready to be read from UDR
  return(UDR); // return the byte
}
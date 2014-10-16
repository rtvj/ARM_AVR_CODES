/****************************************************************************************
FileName		:	serial_main.c
ProjectName		:	UART TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Author			:	TEAM
Description		:	This is a program for testing UART
****************************************************************************************/

#include<avr/io.h>
#include "Serial.h"

int main(void)
{
DDRC = 0XFF;
PORTC = 0XFF;
	unsigned char readch;
	Serial_Init();
	print_string("\n\rSTART ");
	print_string("\n\rPress any key ...");
	PORTC=0xfc;
	readch = USART_Receive();	/* read a character from UART */
	PORTC=0xfe;
	USART_Transmit(readch);		/* write a character from UART */
	PORTC=0xf8;
	print_string("\n\rEND OF MAIN ");
	DDRB = 0XFF;
	DDRE = 0XFF;
	while(1)
	{
		PORTB = 0X30;
		PORTE = 0X05;
	}
}

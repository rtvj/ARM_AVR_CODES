/*****************************************************************
Filename	: myuart.h
Target		: ATmega128
Frequency	: 16Mhz
Compiler	: avr-gcc
Author		: TEAM
Description	: this is UART Library
*****************************************************************/
#include<avr/io.h>

#ifndef MYUART_H
#define MYUART_H 1

void UART_config(unsigned long int baudrate)
{
	unsigned int UBRR_set=0, UBRR_low, UBRR_high;
	unsigned long int arr1[]={2400,4800,9600,14400,19200,28800,38400,57600,76800,115200};
	unsigned int arr2[]={415,207,103,68,51,34,25,16,12,8};

	UCSR1B = 0x18;  //polled transmission,polled reception, 8-bits
	UCSR1C = 0x06;  //1 stop bit, no parity

	for(int cnt=0;cnt<10;cnt++)
	{
		if(arr1[cnt]==baudrate)
			UBRR_set=arr2[cnt];
	}
	UBRR_high=UBRR_set/256;
	UBRR_low=UBRR_set%256;

	UBRR1L=(unsigned char)UBRR_low;
	UBRR1H=(unsigned char)UBRR_high;
}
/* Function to transmit a single character using UART*/
void UART_Transmit_char(unsigned char ch)
{
	while(!(UCSR1A&0b00100000));
	UDR1=ch;
}
/* Function to recaive a single charcter using UART*/
unsigned char UART_Receive_char(void)
{
	while(!(UCSR1A&0b10000000));
	return UDR1;
}
void UART_Transmit_string(unsigned char *str)
{
	while(*str!='\0')
	{
		UART_Transmit_char(*str);
		str++;
	}
}
void UART_Transmit_num(unsigned int num)
{
	unsigned char ch[3],count=2;	

	ch[0]=0;
	ch[1]=0;
	ch[2]=0;

	while(num!=0)
	{
		ch[count]=num%10;
		num=num/10;
		count--;
	}
	for(count=0;count<3;count++)
	{
		UART_Transmit_char('0'+ch[count]);
	}
}
	
/* function to receive a string usins UART*/
unsigned char * UART_Receive_string(void)
{
	unsigned char ch1,str[100],count=0;
	while((ch1=UART_Receive_char())!=13)
	{
		str[count]=ch1;
		count++;
	}
	str[count]='\0';
	return str;
}
#endif

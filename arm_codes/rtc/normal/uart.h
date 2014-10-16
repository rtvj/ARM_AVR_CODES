#include"startup.h"
#include"LPC214x.h"

#define val 60000000/(16*baud)
#define baud 9600
void uart0_init()
{
	PINSEL0&=~(1<<1)|(1<<3);
	PINSEL0|=(1<<0)|(1<<2);
	
	U0LCR|=(1<<7);// enable DLAB bit
	U0DLL=val&(0xFF);
	U0DLM=val>>8;
	U0LCR=0X03;//parity disable,1 stop bit,8 bit data
}

void uart0_tx_char(unsigned char data)
{
	while(!(U0LSR&(1<<5)));  
	U0THR=data;
}	

void uart0_tx_str(unsigned char *ptr) 
{
    while(*ptr !='\0')
	{
	uart0_tx_char(*ptr);
	ptr ++; // uart1_tx_char(*(ptr++));
	}
}

void uart0_tx_num(unsigned int num ) 
{
	unsigned char i,count[5];	
	
	for(i=1;i<=4;i++)
	{
	count[i] = num % 10;
	num = num / 10 ;
	}
	i--;// At the time of exit from the 'for loop',its value is greater than 1 of max value,
		// in this case it is 6 which is greater than 5;hence to decrease by 1 i--. 
	while(i!=0)
	{
	uart0_tx_char(count[i] + 0x30);
	i--;
	}
}
unsigned char uart0_rx_char(void)
{
	while(!(U0LSR&(1<<0)));  
	return U0RBR;
}
	
void uart0_rx_str(unsigned char *ptr)
{     unsigned int i;
      for(i=0;i<100;i++)
      {
       *(ptr+i)=uart0_rx_char();
        if(*(ptr+i)=='\r')
        {
        *(ptr+i)='\0';
		
        break;
		}
       }      
}	

// Receiving number
//For 1 digit no.
unsigned char uart0_rx_num(void)
{
	unsigned char num;
	while(1)
	{
	num = uart0_rx_char();
	num = num - 0x30;
	return num;
	}
}

// For 2 digit no.
/*
unsigned char uart0_rx_num(void)
{
	unsigned char num,num1;
	while(1)
	{
	num = uart0_rx_char();
	num1 = num - 0x30;
	
	num = uart0_rx_char();
	num = ((num1 * 10 ) + (num - 0x30));
	return num;
	}
}	
*/
 
	
	

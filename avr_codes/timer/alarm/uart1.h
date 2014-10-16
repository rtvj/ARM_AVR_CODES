#include<avr/io.h>

// INITIALIZATION FUNCTION FOR UART1
void uart1_init(void) 
{
	UBRR1H = 0;
	UBRR1L = 103; //0X67; BAUDRATE = 9600

	UCSR1C |= (1<<UCSZ1) | (1<<UCSZ0); //UCSR1C = 0X06;// frame : 8 bit data , no parity , stop bit

	UCSR1B |= (1<<RXEN) | (1<<TXEN);// ENABLE TRANSMITTER & RECEIVER
}

// TRANSMITTING CHAR
void uart1_tx_char(unsigned char data)
{
	while(!(UCSR1A &(1<<UDRE)));
	UDR1 = data;
}

//Transmitting string
void uart1_tx_str(unsigned char *ptr) 
{
    while(*ptr !='\0')
	{
	uart1_tx_char(*ptr);
	ptr ++;
	}
}

// Transmitting number
void uart1_tx_num(unsigned int num ) 
{
	unsigned char i,count[5];	
	
	for(i=1;i<=5;i++)
	{
	count[i] = num % 10;
	num = num / 10 ;
	}
	i--;
	
	while(i!=0)
	{
	uart1_tx_char(count[i] + 0x30);
	i--;
	}
}

// Recieving char
unsigned char uart1_rx_char(void) 
{
	while(!(UCSR1A &(1<<RXC)));
	return UDR1;
}

// Recieving string
void uart1_rx_str(unsigned char *ptr)
{     unsigned char i;
      for(i=0;i<10;i++)
      {
       *(ptr+i)=uart1_rx_char();
        if(*(ptr+i)=='\r')
        {
        *(ptr+i)='\0';
		
        break;
		}
       }      
}

// Recieving number
unsigned char uart1_rx_num(void)
{
	unsigned char num,num1;
	num = uart1_rx_char();
	num1 = num - 0x30;
	num = uart1_rx_char();
	num = ((num1 * 10 ) + (num - 0x30));
	return num;
}
	

 


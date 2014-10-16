//#include<avr/io.h>

void uart0_init(void) // INITIALIZATION FUNCTION
{
	UBRR0H = 0;
	UBRR0L = 25; //0X67; BAUDRATE = 9600

	UCSR0C = 0X06;// frame : 8 bit data , no parity , stop bit
	//UCSR1C |= (1<<UCSZ1) | (1<<UCSZ0);

	UCSR0B |= (1<<RXEN) | (1<<TXEN)|(1<<RXCIE);// ENABLE TRANSMITTER & RECEIVER
}

void uart0_tx_char(unsigned char data)// TRANSMISSION FUNCTION
{
	while(!(UCSR0A &(1<<UDRE)));
	UDR0 = data;
}

void uart0_tx_str(unsigned char *ptr) //Transmitting string
{
    while(*ptr !='\0')
	{
	uart0_tx_char(*ptr);
	ptr ++;
	}
}

void uart0_tx_num(unsigned int num ) // Transmitting number
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
	uart0_tx_char(count[i] + 0x30);
	i--;
	}
}
unsigned char uart0_rx_char(void)
{
	while(!(UCSR0A &(1<<RXC)));
	return UDR0;
}

void uart0_rx_str(unsigned char *ptr)
{     unsigned char i;
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
	

 


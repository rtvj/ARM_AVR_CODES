
#include<avr/io.h>
#include<util/delay.h>
/***************************************************************************************************************************/

void uart1_init(unsigned long baud)
{
int count;
count=((16000000/(16*baud))-1);       //counting baud rate

UBRR1H=0;                          //seting baud rate for uart1
UBRR1L=count;                      //seting baud rate for uart1
//UBRR1L=103; //0x67

//UCSR1C=0x06;                    //asynchronous,8bit data,no parity,1 stop bit
UCSR1C|=(1<<UCSZ1)|(1<<UCSZ0);   //asynchronous,8bit data,no parity,1 stop bit
UCSR1B|=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);       //ENABLE TX AND RX (uscr1b=0x18)

}

void uart0_init(unsigned long baud)
{
int count;
count=((16000000/(16*baud))-1);       //counting baud rate

UBRR0H=0;                          //seting baud rate for uart0
UBRR0L=count;                      //seting baud rate for uart0
//UBRR0L=103; //0x67

//UCSR0C=0x06;                    //asynchronous,8bit data,no parity,1 stop bit
UCSR0C|=(1<<UCSZ1)|(1<<UCSZ0);   //asynchronous,8bit data,no parity,1 stop bit
UCSR0B|=(1<<RXEN)|(1<<TXEN)|(1<<RXCIE);       //ENABLE TX AND RX (uscr0b=0x18)
}


/***********************************************************************************************************************/

void uart1_tx_char(unsigned char Data)
{
while(!(UCSR1A&(1<<UDRE)));     //CHEKING DATA REGISTER (UDR1) IS EMPTY OR NOT
UDR1=Data;
_delay_ms(41);
}

void uart1_tx_str(unsigned char *ptr)
{
while(*ptr!='\0')     
{
uart1_tx_char(*ptr);
ptr++;
}
}


void uart1_tx_num(unsigned int val)                                                  //for 4 digit value
{
unsigned char count[5],i;
for(i=1;i<5;i++)
{
count[i]=val%10;                      //for separating unit places
val=val/10;
}
i--;
while(i!=0)
{
uart1_tx_char(count[i]+0x30);         //converting decimal to ASCII value
i--;
}
}

void uart1_tx_num2(unsigned int val)                                                   //for 2 digit value
{
unsigned char count[2],i;
for(i=1;i<3;i++)
{
count[i]=val%10;                      //for separating unit places
val=val/10;
}
i--;
while(i!=0)
{
uart1_tx_char(count[i]+0x30);         //converting decimal to ASCII value
i--;
}
}



unsigned char uart1_rx_char()
{
while(!(UCSR1A&(1<<RXC)));              //CHEKING DATA REGISTER (UDR1) IS EMPTY OR NOT

return UDR1;
}

void uart1_rx_str(unsigned char *ptr)
{
int i;
for(i=0;i<100;i++)
{
*(ptr+i)=uart1_rx_char();
if(*(ptr+i)=='\r')
{
*(ptr+i)='\0';
break;
}
}
}


unsigned int uart1_rx_num()
{
int i,num;
unsigned char count[6];
for(i=0;i<6;i++)
{
num=uart1_rx_char();
count[i]=num-0x30;
if(num=='\r')
{
break;
}
}
i--;
num=count[i]+(count[i-1]*10)+(count[i-2]*100)+(count[i-3]*1000);
return num;
}

unsigned int uart1_rx_num3()
{
unsigned int i=0,num=0;
unsigned char count[5],U=0,T=0,H=0;
for(i=1;i<5;i++)
{
num=uart1_rx_char();
count[i]=num-0x30;
if(num=='\r')
{
break;
}
}
i--;
U=count[i];
T=(count[i-1]*10);
H=(count[i-2]*100);
	uart1_tx_char(U+48);
	uart1_tx_char(T+48);
	uart1_tx_char(H+48);
}
/*
do{
	num=uart1_rx_char(); 
	count[i]=num-0x30; uart1_tx_num(count[i]);uart1_tx_char('\n');
	i++; 
  }while(num!='\r'); uart1_tx_num(count[i]);uart1_tx_char('\n');
i--; uart1_tx_num(i);uart1_tx_char('\n');
i--;
uart1_tx_num(count[i]);uart1_tx_char('\n');
uart1_tx_num(count[i-1]);uart1_tx_char('\n');
uart1_tx_num(count[i-2]);uart1_tx_char('\n');

num=(count[i]+(count[i-1]*10)+(count[i-2]*100)+(count[i-3]*1000));
uart1_tx_num(num);uart1_tx_char('\n');
return num;
}
*/
unsigned int uart1_rx_num2()
{
unsigned char num,num1;
num=uart1_rx_char();
num1=num-0x30;
num=uart1_rx_char();
num=((num1*10)+(num-0x30));
return num;
}
/*******************************************************************************************************************************************/


void uart0_tx_char(unsigned char Data)                     //UART0 TRANSMITTE
{
while(!(UCSR0A&(1<<UDRE)));     //CHEKING DATA REGISTER (UDR1) IS EMPTY OR NOT
UDR0=Data;
}


void uart0_tx_str(unsigned char *ptr)
{
while(*ptr!='\0')     
{
uart0_tx_char(*ptr);
ptr++;
}
}


void uart0_tx_num(unsigned int val)
{
unsigned char count[5],i;
for(i=1;i<5;i++)
{
count[i]=val%10;                      //for separating unit places
val=val/10;
}
i--;
while(i!=0)
{
uart0_tx_char(count[i]+0x30);         //converting decimal to ASCII value
i--;
}
}

void uart0_tx_num2(unsigned int val)                                                   //for 2 digit value
{
unsigned char count[2],i;
for(i=1;i<3;i++)
{
count[i]=val%10;                      //for separating unit places
val=val/10;
}
i--;
while(i!=0)
{
uart0_tx_char(count[i]+0x30);         //converting decimal to ASCII value
i--;
}
}

unsigned char uart0_rx_char()                                      //UART0 RECEIVE
{
while(!(UCSR0A&(1<<RXC)));              //CHEKING DATA REGISTER (UDR1) IS EMPTY OR NOT

return UDR0;
}


void uart0_rx_str(unsigned char *ptr)
{
int i;
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

unsigned int uart0_rx_num()
{
int i,num;
unsigned char count[6];
for(i=0;i<6;i++)
{
num=uart0_rx_char();
count[i]=num-0x30;
if(count[i]=='\r')
{
break;
}
}
i--;
num=count[i]+(count[i-1]*10)+(count[i-2]*100)+(count[i-3]*1000);
return num;
}

unsigned int uart0_rx_num3()
{
unsigned int i=0,num=0;
unsigned char count[5],U=0,T=0,H=0,TH;
for(i=1;i<5;i++)
{
num=uart0_rx_char();
count[i]=num-0x30;
if(num=='\r')
{
break;
}
}
i--;
TH=count[i]/1000;
	H=(num-(TH*1000))/100;
	T=(num - (TH*1000)-(H*100))/10;
	U=(num - (TH*1000)-(H*100) - (T*10));
	
	uart0_tx_char(TH+48);
	uart0_tx_char(H+48);
	uart0_tx_char(T+48);
	uart0_tx_char(U+48);		
/*	
U=count[i];
T=(count[i-1]*10);
H=(count[i-2]*100);
*/	
}

unsigned int uart0_rx_num2()
{
unsigned char num,num1;
num=uart0_rx_char();
num1=num-0x30;
num=uart0_rx_char();
num=((num1*10)+(num-0x30));
return num;
}

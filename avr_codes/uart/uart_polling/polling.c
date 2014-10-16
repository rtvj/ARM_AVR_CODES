#include<util/delay.h>
#include"uart0.h"
#include"uart1.h"
int main(void)
{

	uart1_init() ; // uart1 initialization
	//uart0_init();  // uart0 initialization
	
	//uart1_tx_char('A'); // char transmission
	
	//uart1_tx_str("nikhil"); // string transmission

	//uart1_tx_num(1); // number transmission
	
	
	// char reception
	/*
	unsigned char ch;
	while(1)
	{
	ch = uart1_rx_char();
	uart1_tx_char(ch);
	} 
	*/
   	
	// string reception
	/*
	unsigned char mystr[100];
	while(1)
	{
	uart1_rx_str(mystr);
	uart1_tx_str(mystr);
	}
 	*/
	
	// num reception
	/*
	while(1)
	{
	unsigned char a;
	a=uart1_rx_num() ;
	uart1_tx_num(a) ;
	}
	*/
	
	
	//COMMUNICATION USING UART1 & UART0
	
	unsigned char *ch;
	//unsigned char data;
	
	//while(1)
	//{
	*ch=0;
	ch = uart1_rx_str();
	while(*ch!='\0'){
	uart1_tx_char(*ch);
	ch++;
	}
	//data = uart0_rx_char();
	//uart1_tx_char(data);
	//} 
	
	 
}
	

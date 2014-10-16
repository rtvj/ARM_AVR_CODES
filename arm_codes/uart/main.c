#include"uart.h"
void main()
{
	sys_init();//for pll
	uart0_init();
	while(1) {
	//uart0_tx_char('A');
	/*unsigned char ch;
	while(1)
	{
	ch=uart0_rx_char();
	uart0_tx_char(ch);
	}
	*/
	
	unsigned char mystr[100];
	uart0_rx_str(mystr); 
	uart0_tx_str(mystr); 
	
	
	uart0_tx_num(1234);
	/*unsigned int ch;
	ch=uart0_rx_num();
	uart0_tx_num(ch);
	*/
}
}
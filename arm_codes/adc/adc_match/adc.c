#include"startup.h"
#include"LPC214x.h"
#include"adc_match.h"
#include"uart.h"
//#include"timer_poll.h"
int main()
{	unsigned int ad;
	sys_init();//for pll
	adc_init();
	uart0_init();
	timer_init();

	while(1)
	{
	ad=adc_read();
	uart0_tx_num(ad); 
	uart0_tx_str("\n");
	}
}	
	


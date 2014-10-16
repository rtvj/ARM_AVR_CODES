#include"startup.h"
#include"LPC214x.h"
#include"adc_burst.h"
#include"uart.h"
int main()
{	unsigned int a=0,c=0,z;
	sys_init();//for pll
	adc_init();
	uart0_init();

	//while(1)
	//{
		for(z=0;z<=9;z++)
		{
			a=adc_read();
			uart0_tx_num(a); 
			c=c+a;
			delay(2000);
			//uart0_tx_num(c); 
			uart0_tx_str("\n");
		}
		
		uart0_tx_str("Average value = ");
		c=c/10;
		uart0_tx_num(c); 
		uart0_tx_str("\n");
	
		
	//}
	
}	
	


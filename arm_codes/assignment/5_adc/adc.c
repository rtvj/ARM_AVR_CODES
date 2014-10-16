#include"startup.h"
#include"LPC214x.h"
#include"adc_burst.h"
#include"uart.h"
#include"lcd_2148.h"
int main()
{	unsigned int a=0,c=0,z;
	sys_init();//for pll
	adc_init();
	lcd2148_init();
	uart0_init();
	 lcd2148_showvalue(1234);
/*
	while(1)
	{
		for(z=0;z<=9;z++)
		{
			a=adc_read();
			//uart0_tx_num(a); 
			lcd2148_showvalue(a);
			c=c+a;
			delay(2000);
			//uart0_tx_num(c); 
			//uart0_tx_str("\n");
			lcd2148_cmd(0x01);
		}
		lcd2148_string("Avg val = ");
		//uart0_tx_str("Average value = ");
		c=c/10;
		lcd2148_gotoxy1(11);
		lcd2148_showvalue(c);
		//uart0_tx_str("\n");
	
		
	}*/
	
}	
	


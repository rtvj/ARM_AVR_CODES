/* Same program as wdt2.c  Here wdt_enable(7) called from wdt.h*/
#include<avr/wdt.h>
#include"uart1.h"
#include<util/delay.h>


int main()
{
	uart1_init();
	wdt_enable(7);// watchdog reset period = 2 sec
	uart1_tx_str("\ncontroller is reset..main program starts..\n");
	
	while(1)
	{
		uart1_tx_str("\nwdt reset....in while loop");
		_delay_ms(2500);
		wdt_reset();
	}
}
 

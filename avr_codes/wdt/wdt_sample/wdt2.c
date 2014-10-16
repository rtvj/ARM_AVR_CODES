//#include<avr/wdt.h> // not reqd if asm instr written
#include"uart1.h"
#include<util/delay.h>


void enable() // To enable Watchdog Timer
{
// follow safety level 2(Watchdog Timer is always enabled)...WDTON=programmed,M103C=unprogrammed
// Refer Datasheet pg 57 safety level 2
	WDTCR|=(1<<WDCE)|(1<<WDE);
	WDTCR|=(1<<WDP2)|(1<<WDP1)|(1<<WDP0)&(~(1<<WDCE));// WDP= To determine time-out period
                                                         //in this case 2.1ms 
}
int main(void)
{
	uart1_init();
	
	uart1_tx_str("\ncontroller is reset..main program starts..\n");
	enable();
	
	while(1)
	{
	/*	When the Watchdog times out,the ATmega64A resets and executes from the Reset Vector.
	i.e.from main program. 
		In this case, for delay_ms < 2.1 ms, Watchdog does not time out 
	i.e. program remains in while loop only.
		For delay_ms > 2.1 ms, Watchdog  times out i.e. program starts from main program.
	*/
		
		uart1_tx_str("\nwdt reset....in while loop");
		_delay_ms(2200);
		
		//wdt_reset(); // watchdog timer reset using wdt.h
		__asm__ __volatile__ ("wdr");// watchdog timer reset 
	}
}

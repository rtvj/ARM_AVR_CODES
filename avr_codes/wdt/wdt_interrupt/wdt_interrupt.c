//#include<avr/wdt.h> // not reqd if asm instr written
#include"uart1.h"
#include<util/delay.h>
#include<avr/interrupt.h>
#include"timer.h"
#include"ext_interrupt.h"
ISR(INT6_vect)
{
	/*	When the Watchdog times out,the ATmega64A resets and executes from the Reset Vector.
	i.e.from main program. 
		In this case, for delay_ms < 2.1 ms, Watchdog does not time out (only wdt resets)
	i.e. program remains in while loop only.
		For delay_ms > 2.1 ms, Watchdog  times out,hence ATmega64A resets 
	and executes from the Reset Vector i.e. program starts from main program.
	*/
		
	_delay_ms(1200);// 1s + 1.2s = 2.2s, hence controller is reset 
	
	/*DDRC= 0XFF;
	PORTC = 0X00;*/
	
}

void enable()  // To enable Watchdog Timer
{
// follow the safety level 2... WDTON=programmed , M103C = unprogrammed
	WDTCR|=(1<<WDCE)|(1<<WDE);
	WDTCR|=(1<<WDP2)|(1<<WDP1)|(1<<WDP0)&(~(1<<WDCE));

}
int main(void)
{
	uart1_init();
	timer_init();
	eint_init();
	
	enable();
	sei();
	uart1_tx_str("\ncontroller is reset..main program starts..\n");
	
	
	
	while(1)
	{
		uart1_tx_str("\nwdt reset....in while loop");
		sec_delay();
		
		//wdt_reset(); // watchdog timer reset using wdt.h
		__asm__ __volatile__ ("wdr");// watchdog timer reset 
	}
}

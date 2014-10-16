#include"startup.h"
#include"LPC214x.h"
#include"rtc_alarm.h"
#include"uart.h"
#include"timer_poll.h"
#include"VIClowlevel.h"
void Timer0_Isr(void)__attribute__((interrupt("IRQ")));
volatile unsigned int secover_Intflag = 0;
unsigned int sec_read,min_read,hour_read,dow_read,dom_read,month_read,year_read,mystr[50];
char days[7][10]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday",};

int main()
{	
	sys_init();//for pll
	uart0_init();
	timer_interrupt_init();
	VICVectAddr1 = (unsigned int)Timer0_Isr; 
	VICVectCntl1 |= 0x20 | 0x4; 
	VICIntEnable |= 0x00000010;
	rtc_write();
	alarm_start();
	alarm_stop(3);
	buzzer_init();
	
	rtc_init();
	 enableIRQ();
	while(1)
	{
	sec_read=rtc_read_sec();
	min_read=rtc_read_min();
	hour_read=rtc_read_hour();
	dow_read=rtc_read_dow();
	dom_read=rtc_read_dom();
	month_read=rtc_read_month();
	year_read=rtc_read_year();
/*	
	if (dow_read==0x00)
		sprintf(mystr,"Day:Monday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);

	else if (dow_read==0x01)
		sprintf(mystr,"Day:Tuesday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);

	else if (dow_read==0x02)
		sprintf(mystr,"Day:Wednesday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);

	else if (dow_read==0x03)
		sprintf(mystr,"Day:Thursday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n"dom_read,month_read,year_read,hour_read,min_read,sec_read);

	else if (dow_read==0x04)
		sprintf(mystr,"Day:Friday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n"dom_read,month_read,year_read,hour_read,min_read,sec_read);
	
	else if (dow_read==0x05)
		sprintf(mystr,"Day:Saturday Date:%02d/%02d/%02d Time: %02d:%02d:%02
d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);
	
	else if (dow_read==0x06)
		sprintf(mystr,"Day:Sunday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);
*/
if(secover_Intflag)
{	
sprintf(mystr,"Day:%s Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",
days[dow_read],dom_read,month_read,year_read,hour_read,min_read,sec_read);
	uart0_tx_str(mystr);
	secover_Intflag=0;
}	
	if(ILR &(1<<0))
	{
		ILR|=(1<<0);
		IOSET0|=(1<<11);
	}
	if(ILR &(1<<1))
	{
		ILR|=(1<<1);IOCLR0|=(1<<11);
		
	}	
	
	}
}	

void Timer0_Isr(void)
{

	static unsigned int count = 999;
	count--;
	if(count!=0)
	{
		count = 999;
		secover_Intflag = 1;
	}
    	T0IR |= 1;		/* Clear interrupt flag */
	VICVectAddr = 0;
}	


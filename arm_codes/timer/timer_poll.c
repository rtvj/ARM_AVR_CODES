#include"startup.h"
#include"LPC214x.h"
#include"uart.h"
#include"timer_poll.h"
int main(void)
{
	unsigned char sec = 0,min=0,hour=0,mystr[30];
	sys_init();//for pll
	uart0_init();
	uart0_tx_str("Digital Clock");
	timer_init();

	while(1)
	{
		sec_delay();// 1 sec has elapsed
		sec++;
		if(sec>59)
		{	
			sec=0;// 1 min has elapsed
			min++;
		}
		if(min>59)
		{	
			min=0;// 1 hour has elapsed
			hour++;
		}
		if(hour>23)
		{	
			hour=0;
		}
		
		sprintf(mystr,"Time: %02d:%02d:%02d\n",hour,min,sec);//inbuilt library function 
		uart0_tx_str(mystr) ;
	}
}

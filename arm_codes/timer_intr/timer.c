#include"startup.h"
#include"LPC214x.h"
#include"uart.h"
#include"timer.h"
#include"lcd_2148.h"
volatile unsigned char count,sec = 0,min=0,hour=0,mystr[35];
int main(void)
{
	
	sys_init();//for pll
	uart0_init();
	lcd2148_init();
	uart0_tx_str("Digital Clock\n");
	timer_init();
	enableIRQ();
	while(1)
	{       /*
		while(!(T0IR&(1<<0)));
		sec++;*/
		
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
			min=0;
			sec=0;
			sec++;
		}
		/*if(count)
		{
		count=0;*/
		sprintf(mystr,"Time: %02d:%02d:%02d\n",hour,min,sec);//inbuilt library function 
		//uart0_tx_str(mystr);
		lcd2148_cmd(0x01);
		delay(1);
		lcd2148_string(mystr);
		uart0_tx_str(mystr);
		uart0_tx_char('\n');
	
		
	}
}

void TIMER0_ISR(void)
{
	
	 uart0_tx_str("in ISR......\n");
	T0IR=(1<<0); 
	sec++;
	VICVectAddr=0x00;
}

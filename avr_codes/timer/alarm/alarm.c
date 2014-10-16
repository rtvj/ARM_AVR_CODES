#include<avr/interrupt.h>
#include<util/delay.h>
#include"timer.h"
#include"uart1.h"
#include"ext_interrupt.h"

volatile unsigned char s,h,m;

ISR(INT6_vect)
{
	uart1_tx_str("Enter the valurs of Alarm Settings :") ;
	uart1_tx_str("HH");
	h=uart1_rx_num() ;
	uart1_tx_num(h) ;
	uart1_tx_str("\nMM");
	m=uart1_rx_num() ;
	uart1_tx_num(m) ;
	uart1_tx_str("\nSS");
	s=uart1_rx_num() ;
	uart1_tx_num(s) ;
}




int main(void)
{
	unsigned char sec = 0,min=0,hour=0,mystr[30];
	uart1_init();
	uart1_tx_str("Digital Clock") ;
	timer_init();
	eint_init();
	sei();
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
		
		sprintf(mystr,"Time: %02d:%02d:%02d\n",hour ,min,sec);//inbuilt library function 
		uart1_tx_str(mystr) ;
		
		if(sec==s && min==m && hour ==h)
		{
			PORTA |=(1<<3);         //buzzer on..connected in active high fashion
    			_delay_ms(1000);
    			PORTA &=~(1<<3);	//buzzer off
	 		_delay_ms(1000);
		}	
	}
}

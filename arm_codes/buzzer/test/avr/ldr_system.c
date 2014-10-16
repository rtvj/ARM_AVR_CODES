#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"uart1.h"
#include"ldr_isr.h"
#include"i2c_12.h"
int main(void)
{
	ldr_init();
	uart1_init();
	i2c_init();
	i2c_write();// write function for RTC
	//uart1_tx_str("uart initialised\n");
	sei();// global enable interrupt
	DDRA |=(1<<3); // buzzer as o/p
	while(1);
}

ISR(ADC_vect)
{
	unsigned int a;
	unsigned char b;
	
	ADCSRA|= (1<<ADSC);// ALWAYS SET START CONV BIT FOR NORMAL MODE
	                    
	b=ADCL;//Read Lower Result Data Reg
	a=ADCH;//Read higher Result Data Reg
	a=(b|(a<<8));//combine two result 

	if(a>40)
	{
	uart1_tx_str("LDR value: ");
	uart1_tx_num(a);
	uart1_tx_str("\n");
	_delay_ms(500);
	
	 PORTA |=(1<<3);     //buzzer on..connected in active high fashion
    	_delay_ms(1000);
   	 PORTA &=~(1<<3);	//buzzer off
	 _delay_ms(1000);

	i2c_read();// read function for RTC
	}

}

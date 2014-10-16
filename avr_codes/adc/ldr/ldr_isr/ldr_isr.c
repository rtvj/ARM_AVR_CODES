#include<util/delay.h>
#include<avr/interrupt.h>
#include"uart1.h"
#include"ldr_isr.h"
int main(void)
{
	ldr_init();
	uart1_init();
	uart1_tx_str("uart initialised\n");
	sei();
	DDRA |=(1<<3); // buzzer as o/p
	while(1);
}

/* o/p for general
ISR(ADC_vect)
{
	uart1_tx_num(ADCH);
	ADCSRA|=  (1<<ADSC);// ALWAYS SET START CONV BIT FOR NORMAL MODE
	uart1_tx_char('\t');
}
*/

ISR(ADC_vect)
{
	int a;
	ADCSRA|= (1<<ADSC);// ALWAYS SET START CONV BIT FOR NORMAL MODE
	                    //Necessary to set in ldr_init() as well as in ISR
	a = ADCH;
	

	uart1_tx_num(ADCH);// 8 bit resolutn,hence no need od ADCL 
	uart1_tx_char('\t');
	_delay_ms(500);
	
	if(a>50)
	{
	 
	PORTA |=(1<<3);     //buzzer on..connected in active high fashion
    _delay_ms(1000);
    PORTA &=~(1<<3);	//buzzer off
	 _delay_ms(1000);
	}

}

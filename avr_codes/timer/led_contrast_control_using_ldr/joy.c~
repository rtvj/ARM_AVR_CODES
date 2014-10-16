#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include"LCD.h"

int main(void)
{
	ADMUX=0XE0;	//MUX0=1, RFES1=1, REFS0=1 for internal 2.6v ADLAR=1 for left adjust ldr on chanl 0
	ADCSRA=0XEF;	//ADPS2:0=111 for 128 prescalar, ADIE=1 interrupt enable, ADATE=1 auto trigger enable, ADSC=1 to start conversion, ADEN=1 to 						enable the ADC
	lcd_init();
	sei();
	DDRC=0XFF;
	while(1)
	{
	
	}
	return 0;
}

ISR(ADC_vect)
{	
	int a;
	a=ADCH;
	PORTC=0X00;
	_delay_us(a);
	//lcd_gotoxy1(0);
	//lcd_char(a);
	PORTC=0XFF;//changed value from ff to 00
	_delay_us(255-a);
	//_delay_us(255-a);
	//lcd_gotoxy2(0);
	//lcd_char(255-a);
}

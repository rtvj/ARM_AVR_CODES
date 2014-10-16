#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned char b = 0;
unsigned int a = 0;
void x_axis()
{
	/*unsigned char b=0;
	unsigned int a=0;	
	*/
	ADMUX=0xc1;//Internal 2.56V Voltage Reference,
//ADLAR=0- Right alligned (10 bit resolutn), MUX 4:0 = 00001 - Single Ended Input ADC1 CHANNEL. 
//Joystick is connected to the ADC, X axis on channel 1 (PF1) of the Atmega64 microcontroller
	
	ADCSRA=0xe4;/*ADC Enable,ADC Start Conversion,Auto Trigger Enable;
	  ADPS bits determine the division factor between the XTAL frequency and the input clock to the
	ADC,ADC Prescaler=128 selected*/
	
	ADCSRB=0X00;// Free Running mode by default(No need to set this reg)
	
	while(!(ADCSRA&(1<<ADIF)));//ADIF bit is set when an ADC conversion completes 
    //and the data registers are updated ,hence wait till ADIF BECOMES 1
	
	b = ADCL;//Read Lower Result Data Reg
	a = ADCH;//Read higher Result Data Reg
	a = ((a<<8) | b );//combine two result (Refer notebook )
	
	uart1_tx_num(a);
	_delay_ms(500);
}

void y_axis()
{
	/*unsigned char b=0;
	unsigned int a=0;	
	*/
	ADMUX=0xc2;//Internal 2.56V Voltage Reference,
//ADLAR=0- Right alligned (10 bit resolutn), MUX 4:0 = 00010 - Single Ended Input ADC2 CHANNEL. 
//Joystick is connected to the ADC, Y axis on channel 2 (PF2) of the Atmega64 microcontroller

	ADCSRA=0xe4;//same as above
	
	ADCSRB=0X00;//same as above
     
	while(!(ADCSRA&(1<<ADIF)));//same as above

	b = ADCL;
	a = ADCH;
	a = ((a<<8) | b );
	
	uart1_tx_num(a);
	_delay_ms(500);
}



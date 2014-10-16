
void ldr_init(void)
{	
	ADMUX|=(1<<REFS1)|(1<<REFS0);//Internal 2.56V Voltage Reference,
	//ADLAR=0- Right alligned (10 bit resolutn), MUX 4:0 = 00000 - Single Ended Input ADC0 CHANNEL. 
	//LDR sensor is connected to channel 0 of the Atmega64 microcontroller.

	
	ADCSRA|=(1<<ADEN)|(1<<ADSC)|(1<<ADIE)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	/*ADC Enable,ADC Start Conversion,ADC Interrupt Enable;
	  ADPS bits determine the division factor between the XTAL frequency and the input clock to the
	ADC,ADC Prescaler=128 selected*/

}




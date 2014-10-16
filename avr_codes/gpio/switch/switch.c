#include<avr/io.h>
#include<util/delay.h>

void switch_init(void)
{
      

     DDRD &= ~((1<<6)|(1<<7));   //pin 6 and pin 7 as i/p..switchs are connected
     PORTD |=((1<<6)|(1<<7));	//enable the pull up resistor i.e make switch open (unpressed)
     
     DDRA |=(1<<3);            	// buzzer as o/p
     
     DDRC=0xff;               	// led's as o/p
}

int main (void)
{
   int i;
   switch_init();
   while(1)
  {
   if((PIND &(1<<6))==0)         //switch 1 is pressed
   {
    PORTA |=(1<<3);         	//buzzer on..connected in active high fashion
    _delay_ms(1000);
    PORTA &=~(1<<3);		//buzzer off
	 _delay_ms(1000);
    }
   else if((PIND &(1<<7))==0)      //switch 2 is pressed
   {
        for(i=0;i<=6;i++)
         {
		  PORTC = 0xff;     	// all leds are off
		  PORTC &=~(1<<i);
          PORTC &=~(1<<(i+1));  	//led pattern
         _delay_ms(1000);
          PORTC=0xff;			// all leds off
         }
    }
   else               			//both switches are not pressed
   {
	PORTC = 0x00; 			// all leds are on
	_delay_ms(500);

	PORTC = 0xff;			// all leds are off
	_delay_ms(500);
   }
  }  
return 0;
}
#include <stdint.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include "LCD.h"
#include "Serial.h"

volatile unsigned long int del;
unsigned char str[70]="Hello to every user\n Welcome to ThinkLABS Technosolutions Pvt. Ltd.\n";
unsigned int i,j,data;

void delay_1s(void)
{
	
	for(del=0;del<100000;del++);			// Software Delay 

}
 // Boolean definitions
 typedef enum
 {
     FALSE = 0,
     TRUE  = !FALSE,
 } bool_t;
 
  void tmr_init(void)
 {
     /* Start timer 1 with clock prescaler CLK/1024 */
     /* Resolution is 139 us */
     /* Maximum time is 9.1 s */
    TCCR1A =  (0<<COM1A1)|(0<<COM1A0)|(0<<COM1B1)|(0<<COM1B0)
              |(0<<COM1C1)|(0<<COM1C0)|(0<<WGM11) |(0<<WGM10);

     TCCR1B =  (0<<ICNC1) |(0<<ICES1) |(0<<WGM13) |(0<<WGM12)
              |(1<<CS12)  |(0<<CS11)  |(1<<CS10);
 }
 
 void tmr_start(uint16_t delay_ms)
 {
     // Calculate and set delay
    TCNT1  = (uint16_t) (0x10000 - ((F_CPU/1024)*delay_ms)/1000);
 
    // Clear timer overflow flag by writing a logical 1, other flags are unchanged
     TIFR = (1<<TOV1);
     // NOTE: This line is more efficient than using "TIFR |= (1<<TOV1);"
 }
 
 bool_t tmr_has_expired(void)
 {
     // See if timer overflow flag is set
     if(TIFR&(1<<TOV1))
     {
         return TRUE;
     }
     else
     {
         return FALSE;
     }
 }
 
 void tmr_delay(uint16_t delay_ms)
 {
     tmr_start(delay_ms);
     while(!tmr_has_expired())
     {
         ;
     }
 }

 void beep(void)
 {
    // Enable Buzzer
     		PORTA=0x03;
     // Wait 1s
    tmr_delay(2000); //buzzer is OFF for 2s
 
     // Disable Buzzer
    	PORTA=~0x03;
 }
int main()
{
	unsigned char ii,jj;
	DDRC=0xff;
	PORTC=0x00;
	
	DDRD=0x00;	//input port for switch sw1 and sw2
	PORTD=0xFF;	//activate the pullup register
	
	DDRA=0xFF;	
	Serial_Init();	
	lcd_init();
	DDRE &=0x3f;
	PORTE =0xc0;
	
	DDRD=0x3f;
	PORTC=0xC0;
	
	EIMSK=0xE0;
	EICRB=0xFC;
	
	sei();   // For Making SREG =0x80;
	
		for(jj=0;jj<2;jj++){
			for(ii=0;ii<8;ii++){
			for(del=0;del<100000;del++);
				PORTC=(1<<ii);
			}
		}
			lcd_gotoxy1(3);
			lcd_string("Welcome To");
			lcd_gotoxy2(0);
			lcd_string("ThinkLABS Tech");
			for(del=0;del<1000000;del++);
		for(ii=0;str[ii]!='\0';ii++){
			USART_Transmit(str[ii]);
			for(del=0;del<90000;del++);
		}
		
		// Set BUZZER_O as output pin
    		DDRA=0xff;
     // Disable Buzzer
   	PORTA=~0x03;
 
     // Initialise timer
     tmr_init();
 
     // Repeat indefinitely
     for(;;){
         beep();   

         // Wait 2s
         tmr_delay(2000);//buzzer is ON for 2scd 
         
         delay_1s();
		PORTC=PORTC^0xff;
		data =PIND;	//this will make the LED.7 blink till you keep the sw2 pressed and led 6 till you press sw1
		PORTC=data;
		lcd_gotoxy1(4);
		lcd_char(data);	
     }
}





ISR(INT7_vect)
{	
	int j,i=0;
	for(j=0;j<8;j++){
	for(i=0;i<8;i++){
		PORTC =(1<<i);
		delay_1s();
		
	}
	sei();
	}
}


ISR(INT6_vect)
{
	
	int i=0;
	lcd_init();
	while(i<3)
	{
		lcd_gotoxy1(0);
		lcd_string("HELLO WORLD");
		lcd_gotoxy2(0);
		lcd_string("LINE 2 PRINT");
		delay_1s();
		lcd_cmd(0x01);
		sei();
		i++;
	}
}

ISR(INT5_vect)
{	
	int j;
	for(j=0;j<8;j++){
		print_string("INT5 INTERRUPTED NOW Will run 8 times\n");
		sei();	
	}
	
	
}


#include"LPC214x.h"

void TIMER0_ISR(void) __attribute__ ((interrupt("IRQ")));

void timer_init(void)
{
//T0TCR|=(1<<1);               //start the timer(reset TC an PC)
T0CTCR=0X00;                 //select timer mode
T0PR=60;                     //set prescale value to 60 (not fixed just used for simplification)
T0MR0=1000000;               //60Mhz/60=1Mhz , 1/1Mhz=1usec,for 1 sec delay 1sec/1usec=10000 clock               
T0MCR=0X3;                   //generate an interrupt on match & TC tO 00
T0TCR=0X1;                   //start the timer(reset TC an PC)
	
VICIntSelect&=~(1<<4);                  //select TIMER0 as IRQ  
VICIntEnable|=(1<<4);                   //enable IRQ
//VICVectCntl0|=(1<<5)|(1<<2);             //assigning slot and enabling IRQ slot
VICVectCntl0|=0x00000024;
VICVectAddr0=(unsigned int)TIMER0_ISR;     //load vector address(user defined)
}



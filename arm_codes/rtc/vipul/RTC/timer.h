
#include"LPC214x.h"
void timer_init(void)
{
T0TCR|=(1<<1);               //reset TC an PC
T0CTCR=0X00;                 //select timer mode
T0PR=60;                     //set prescale value to 60 (not fixed just used for simplification)
T0MR0=1000000;               //60Mhz/60=1Mhz , 1/1Mhz=1usec,for 1 sec delay 1sec/1usec=10000 clock               
T0MCR=0X3;                   //generate an interrupt on match & TC tO 00
T0TCR=0X1;                   //start the timer
T0IR=0x1;
}
/*
T0TCR=0x2;
T0TCR=0x0;
T0TC=0;
T0MR0=59999;
T0MCR=0x3;
T0TCR=0x1;*/


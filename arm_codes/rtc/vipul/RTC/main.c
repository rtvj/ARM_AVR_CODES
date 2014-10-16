/****************************************************************************************
Tittle		    :  RTC(REAL TIME CLOCK)
Author		    :  VIPUL KUTE
Target		    :  LPC2148(ARM)
CPU Clock	    :  16Mhz
Date            :  19th may 2012
Environment     :  Linux(ubantu)
C-compiler      :  arm-elf-gcc -v
	               Thread model: single
	               gcc version 3.3
***************************************************************************************/	

#include "LPC214x.h"
#include"startup.h"
#include"uart0.h"
#include"lcd_2148.h"
#include"RTC.h"
#include"timer.h"
#include"VIClowlevel.h"
void Timer0_Isr(void)__attribute__((interrupt("IRQ")));
volatile unsigned int secover_Intflag = 0;
volatile unsigned int sec1,min1,hour1,day1,month1,year1,dow1,doy1,mystr[100];

int main()
{


sys_init();
uart0_init(9600);
timer_init();
PINSEL2&=~(1<<3); // to select the bit 1.25 of port1
IODIR1 |=(1<<25); // SET THE 25th pin
IOSET1 |=(1<<25); // BUZZER OFF
VICVectAddr1 = (unsigned int)Timer0_Isr; 
	VICVectCntl1 |= 0x20 | 0x4; 
	VICIntEnable |= 0x00000010;

RTC_write();
alarm_start();
alarm_stop(3);
RTC_init();
 enableIRQ();
while(1)
{
sec1=RTC_read_sec();

min1=RTC_read_min();

hour1=RTC_read_hour();

day1=RTC_read_day();

month1=RTC_read_month();

year1=RTC_read_year();

dow1=RTC_read_dow();

doy1=RTC_read_doy();
if(secover_Intflag)
{	
sprintf(mystr,"RTC_TIME:%02d:%02d:%02d\nDATE:%02d:%02d:%04d\nDay of week:%02d\nDay of year:%03d\n\n",hour1,min1,sec1,day1,month1,year1,dow1,doy1);   //inbuild libray fnction used to creat string
uart0_tx_string(mystr);
secover_Intflag=0;
}
if(ILR &(1<<0))
	{
		ILR|=(1<<0);
		IOSET1|=(1<<25);
	}
	if(ILR &(1<<1))
	{
		ILR|=(1<<1);IOCLR1|=(1<<25);
		
	}	
/*
if(sec1==3)
{
ILR|=(1<<1);
IOCLR1|=(1<<25); // BUZZER ON
}
else
{
ILR|=(1<<0);
IOSET1|=(1<<25); // BUZZER OFF
}*/

}
return 0;
}


void Timer0_Isr(void)
{

	static unsigned int count = 999;
	count--;
	if(count!=0)
	{
		count = 999;
		secover_Intflag = 1;
	}
    	T0IR |= 1;		/* Clear interrupt flag */
	VICVectAddr = 0;
}

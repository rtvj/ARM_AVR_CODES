/****************************************************************************************
Tittle		    :  display time using timer0 using TIMER0 interrupt
Author		    :  VIPUL KUTE
Target		    :  LPC2148(ARM)
CPU Clock	    :  12Mhz
Date            :  19th may 2012
Environment     :  Linux(ubantu)
C-compiler      :  arm-elf-gcc -v
	               Thread model: single
	               gcc version 3.3
***************************************************************************************/	

#include"startup.h"
#include"VIClowlevel.h"
#include"uart0.h"
#include"timer.h"
#include"lcd_2148.h"

volatile unsigned char sec=0,min=0,hr=0;
unsigned char mystr[30];

int main(void)
{
	sys_init();
	lcd_init();
	uart0_init(9600);
	timer_init();
	enableIRQ();
	
	uart0_tx_string("in main program....\n");
	uart0_tx_string("digital clock application....\n");
	
	
	while(1)
	{
	
	if(sec>59)
	{
	sec=0;
	min++;
	}
	if(min>59)
	{
	min=0;
	hr++;
	}
	if(hr>23)
	{
	hr=0;
	min=0;
	sec=0;
	sec++;
	}
	
	sprintf(mystr,"TIME:%02d:%02d:%02d",hr,min,sec);   //inbuild libray fnction used to creat string
	lcd2148_cmd(0x01);
	delay(1);
	lcd2148_string(mystr);
	uart0_tx_string(mystr);
	uart0_tx_char('\n');
	
	}
}

void TIMER0_ISR()
{   
	//uart0_tx_string("in ISR......\n");
	T0IR=(1<<0); 
	sec++;
	VICVectAddr=0x00;
}


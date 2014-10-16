#include"startup.h"
#include"LPC214x.h"
#include"ext_interrupt.h"
#include"VIClowlevel.h"

unsigned int i,j;

void EINT2_ISR(void)
{
buzzer_init();

IOCLR0|=(1<<11);// Turn ON Buzzer
		for(i=0;i<6000;i++)
		{
		for(j=0;j<600;j++);
		}	
		
		for(i=0;i<6000;i++)
		{
		for(j=0;j<600;j++);	
		}
IOSET0|=(1<<11);// Turn OFF Buzzer

EXTINT|=(1<<2);                            //flag clear
VICVectAddr=0x00;
}

int main(void)
{
sys_init();//for pll	
switch_init();

ext_irq();
enableIRQ();
while(1);

}

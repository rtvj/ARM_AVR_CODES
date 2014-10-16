#include"startup.h"
#include"VIClowlevel.h"
#include"uart0.h"


void EXT2_ISR(void) __attribute__ ((interrupt("IRQ")));

int main(void)
{
	sys_init();
	
	PINSEL0|=(1<<31)&(~(1<<30));
	EXTMODE|=(1<<2);
	EXTPOLAR&=~(1<<2);
	EXTINT=(1<<2);
	VICIntSelect&=~(1<<16);
	VICIntEnable|=(1<<16);                     //enable IRQ
	VICVectCntl0|=(1<<5)|(1<<4);               //assigning slot and enabling IRQ slot
    VICVectAddr0=(unsigned int)EXT2_ISR;      //load vector address
    
    uart0_init(9600);
    uart0_tx_string("in main program....\n");
    enableIRQ();
    while(1);
}


void EXT2_ISR(void)
{
	unsigned int i,j;
	PINSEL2&=~(1<<3);
	IODIR1|=(1<<25);
	uart0_tx_string("switch is press....");
		
		IOSET1|=(1<<25);

		for(i=0;i<600;i++)
		{
		for(j=0;j<600;j++);
		}	
		IOCLR1|=(1<<25);
		for(i=0;i<600;i++)
		{
		for(j=0;j<600;j++);	
		}
		
		EXTINT|=(1<<2);                            //flag clear
		VICVectAddr=0x00;
}

#include"startup.h"
#include"VIClowlevel.h"
#include"uart0.h"
#include"ext_int.h"

int main()
{	
	sys_init();         //for pll
		
	uart0_init(9600);
	ext_init();
	enableIRQ();
	uart0_tx_string("in main program....\n");
	while(1);
	return 0;
}

void EXT2_ISR()
{   
	unsigned int i,j;
	
	PINSEL2&=~(1<<3);
	IODIR1|=(1<<25);
	uart0_tx_string("switch is press....");
	
		IOSET1|=(1<<25);        //buzzer on

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

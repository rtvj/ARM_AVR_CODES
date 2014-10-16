#include"LPC214x.h"

void EXT2_ISR(void) __attribute__ ((interrupt("IRQ")));

void ext_init(void)
{                        
	PINSEL0|=(1<<31)&(~(1<<30));             //select EINT2      
	EXTMODE|=(1<<2);                         //EINT2 is edge sensitive.
	EXTPOLAR &=~(1<<2);                      //EINT2 is low-active or falling-edge sensitive (depending on EXTMODE2). 
	EXTINT|=(1<<2);                          //flag clear
    VICIntSelect&=~(1<<16);                  //select EINT2 as IRQ  
    VICIntEnable|=(1<<16);                   //enable IRQ
	VICVectCntl0|=(1<<5)|(1<<4);             //assigning slot and enabling IRQ slot
    VICVectAddr0=(unsigned int)EXT2_ISR;     //load vector address
}


	

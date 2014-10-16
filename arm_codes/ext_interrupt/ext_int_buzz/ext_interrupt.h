// IRQ	
void EINT2_ISR(void) __attribute__ ((interrupt("IRQ")));

void switch_init()
{
	PINSEL0&=~(1<<30);
	PINSEL0|=(1<<31);//   select sw as ext interr.   
	
	//IODIR0&=~(1<<15);// sw AS i/P 
}

void buzzer_init()
{
PINSEL0&=~((1<<22)|(1<<23));//   select  buzzer
IODIR0|=(1<<11);//buzzer AS O/P 
}
	
void ext_irq()
{
EXTMODE|=(1<<2);// edge sensitive
EXTPOLAR&=~(1<<2);// falling edge
EXTINT|=(1<<2);// clear corr. flag by writing 1 to it.
//VICIRQStatus|=(1<<16);// to read status
VICIntSelect&=~(1<<16);//Select as irq 
VICIntEnable|=(1<<16);// to enable EINT2

//VICVectCntl0|=(1<<4)|(1<<5);//0x30  to  assign & enable VIC slot 0 to EINT2
VICVectCntl0=0x30;
//VICVectAddr0=0x00;
VICVectAddr0=(unsigned int)EINT2_ISR;


}

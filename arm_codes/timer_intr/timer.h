
void TIMER0_ISR(void) __attribute__ ((interrupt("IRQ")));
void timer_init()
{
	T0TCR|=(1<<1);//reset TC & PC
	T0CTCR=0X00;// select timer mode on positive rising edge
	T0PR=60;// for 1 sec delay
	T0MR0=1000000;
	//T0IR=(1<<0);
	T0MCR=0x3;//0X3 generate interrupt on match & reset the TC to 00
	T0TCR=0x1;// start the timer.
	VICIntSelect&=~(1<<4);//Select as irq 
	VICIntEnable|=(1<<4);// to enable timer0
	VICVectCntl0|=(1<<5)|(1<<2);    //assigning slot and enabling IRQ slot
	//VICVectCntl0|=0x00000024;//0x30  to  assign & enable VIC slot 0 to TIMER0 ISR
//VICVectAddr0=0x00;
	VICVectAddr0=(unsigned int)TIMER0_ISR;
	
}



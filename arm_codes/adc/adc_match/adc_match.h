void adc_init()
{
	PINSEL1|=(1<<24);
	PINSEL1&=~(1<<25);//AD0.2 at P0.29
	
	AD0CR|=(1<<1)|(12<<8)|(1<<21)|(1<<27)|(5<<24);//AD0.2 ;VPB clock (PCLK) value=12;PDN=1;Start conversion on a falling edge;
					      //(5<<24)=101->Start conversion when the edge selected by bit 27 occurs on MAT0.3.

}

unsigned int adc_read()
{
	//AD0CR|=(1<<24);//001=Start conversion now.
	
	while(!(AD0DR1&(1<<31)));//This bit is set to 1 when an A/D conversion completes,hence poll till it becomes 1.
                               
	return((AD0DR1 & 0x0000FFC0)>>6);//masking(refer notbk)
}


void timer_init()
{
	T0EMR|=(3<<10);//set external match pin for adc start conversion
	T0TCR|=(1<<1);//reset TC & PC
	T0CTCR=0X00;// select timer mode on positive rising edge
	T0PR=60;// for 1 sec delay
	T0MR3=1000000;
	//T0MCR=0x3;//0X3 generate interrupt on match & reset the TC to 00
	T0MCR|=(1<<9)|(1<<10);//Interrupt on MR3,Reset on MR3
	T0TCR=0x1;// start the timer.
}

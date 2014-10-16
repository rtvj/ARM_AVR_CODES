
void timer_init()
{
	T0TCR|=(1<<1);//reset TC & PC
	T0CTCR=0X00;// select timer mode on positive rising edge
	T0PR=60;// for 1 sec delay
	T0MR0=1000000;
	T0MCR=0x3;//0X3 generate interrupt on match & reset the TC to 00
	T0TCR=0x1;// start the timer.
}

void sec_delay()
{
	while(!(T0IR&(1<<0)));
	T0IR|=(1<<0);// CLEAR FLAG 
}


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

void timer_interrupt_init(void)
{
T0TCR|=(1<<1);               //reset TC an PC
T0CTCR=0X00;                 //select timer mode
T0PR=60;                     //set prescale value to 60 (not fixed just used for simplification)
T0MR0=1000000;               //60Mhz/60=1Mhz , 1/1Mhz=1usec,for 1 sec delay 1sec/1usec=10000 clock               
T0MCR=0X3;                   //generate an interrupt on match & TC tO 00
T0TCR=0X1;                   //start the timer
T0IR=0x1;
}

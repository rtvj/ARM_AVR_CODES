unsigned int sec=55,min=55,hour=1,dow=6,dom=2,month=5,year=2012;

void rtc_init()
{
	CCR=0X11;//CLKEN =1;CLKSRC =1
}

void rtc_write()
{
	SEC =sec&0x3f;
	MIN =min&0X3f;
	HOUR =hour&0X1f;
	DOW=dow&0X07;
	DOM = dom&0x1f;
	MONTH =month&0x1f;
	YEAR =year&0x0fff;
}

unsigned int  rtc_read_sec()
{
	return (CTIME0 &0x3f);
}

unsigned int  rtc_read_min()
{
	return ((CTIME0 &0x3f00)>>8);
}

unsigned int  rtc_read_hour()
{
	return ((CTIME0 &0x1f0000)>>16);
}

unsigned int  rtc_read_dow()
{
	return ((CTIME0 &0x7000000)>>24);
}
unsigned int  rtc_read_dom()
{
	return (CTIME1 &0x1f);
}

unsigned int  rtc_read_month()
{
	return ((CTIME1 &0x1f00)>>8);
}

unsigned int  rtc_read_year()
{
	return ((CTIME1 &0xfff0000)>>16);
}
void delay(unsigned int i)
{
	volatile unsigned int j=0,k = 0;
	for (j=0;j<i;j++)
		for (k=0;k<6000;k++);	
}
/*
void alarm_start()
{
	CIIR=0X00;// initialise by 0
	ILR=0X01;// RTCCIF =When one, the Counter Increment Interrupt block generated an interrupt.
	CIIR|=(1<<0);// When 1, an increment of the Second value generates an interrupt. 
}

void alarm_stop(unsigned int val)
{
	ILR=0X02;//RTCALF =When one, the alarm registers generated an interrupt. Writing a one to this bit location clears 		    //	the alarm interrupt
	ALSEC=val;//The values in these registers are compared with the time counters.
	AMR&=~(1<<0);//When 1, the  value is not compared for the alarm;hence 0.
}
*/

void alarm_start()
{
	CIIR=0x00;
	ILR=0x1;			
	CIIR|=(1<<0);
}

void alarm_stop(unsigned int value)
{
	ILR|=0x2;
	ALSEC=value;
	AMR&=~(1<<0);
}



void buzzer_init()
{
PINSEL0&=~((1<<22)|(1<<23));//   select  buzzer
IODIR0|=(1<<11);//buzzer AS O/P 
IOSET0|=(1<<11);
}

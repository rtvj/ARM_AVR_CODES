unsigned int sec=55,min=55,hour=1,dow=2,dom=2,month=5,year=2012;

void rtc_init()
{
	CCR=0X11;//CLKEN =1;CLKSRC =1
}

void rtc_write()
{
	SEC =sec&0x3f;
	MIN =min&0X3f;
	HOUR =hour&0X1f;
	DOW=dow&0X7;
	DOM = dom&0x1f;
	MONTH =month&0x1f;
	YEAR =year&0xfff;
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

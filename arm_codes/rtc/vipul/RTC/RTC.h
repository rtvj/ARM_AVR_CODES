volatile unsigned int sec=0,min=59,hour=1,day=2,month=2,year=1991,dow=4,doy=33;
/*
#define sec   0
#define min   1
#define hour  1
#define day   1
#define month 2
#define year  2012
*/
void RTC_init()
{
CCR=0x11;
//CIIR|=(1<<0)|(1<<1)|(1<<2);
}

void RTC_write()
{
SEC  = sec  & 0x3f;
MIN  = min  & 0x3f;
HOUR = hour & 0x1f;
DOM  = day  & 0x1f;
MONTH= month& 0x0f;
YEAR = year & 0x0fff;
DOW  = dow  & 0x07;
DOY  = doy  & 0x01ff;
}

unsigned int RTC_read_sec()
{
return (CTIME0&0X3F);
}
unsigned int RTC_read_min()
{
return ((CTIME0&0X3F00)>>8);
}
unsigned int RTC_read_hour()
{
return ((CTIME0&0X1F0000)>>16);
}

unsigned int RTC_read_day()
{
return (CTIME1&0X3F);
}
unsigned int RTC_read_month()
{
return ((CTIME1&0X0F00)>>8);
}
unsigned int RTC_read_year()
{
return ((CTIME1&0X0FFF0000)>>16);
}
unsigned int RTC_read_dow()
{
return ((CTIME0&0X07000000)>>24);
}
unsigned int RTC_read_doy()
{
return (CTIME2&0X01FF);
}

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




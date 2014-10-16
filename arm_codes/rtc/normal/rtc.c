#include"startup.h"
#include"LPC214x.h"
#include"rtc.h"
#include"uart.h"
unsigned int sec_read,min_read,hour_read,dow_read,dom_read,month_read,year_read,mystr[20];
char days[7][10]={"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday",};

int main()
{	
	sys_init();//for pll
	uart0_init();
	rtc_init();
	rtc_write();
	while(1)
	{
	sec_read=rtc_read_sec();
	min_read=rtc_read_min();
	hour_read=rtc_read_hour();
	dow_read=rtc_read_dow();
	dom_read=rtc_read_dom();
	month_read=rtc_read_month();
	year_read=rtc_read_year();
/*	
	if (dow_read==0x00)
		sprintf(mystr,"Day:Monday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);

	else if (dow_read==0x01)
		sprintf(mystr,"Day:Tuesday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);

	else if (dow_read==0x02)
		sprintf(mystr,"Day:Wednesday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);

	else if (dow_read==0x03)
		sprintf(mystr,"Day:Thursday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n"dom_read,month_read,year_read,hour_read,min_read,sec_read);

	else if (dow_read==0x04)
		sprintf(mystr,"Day:Friday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n"dom_read,month_read,year_read,hour_read,min_read,sec_read);
	
	else if (dow_read==0x05)
		sprintf(mystr,"Day:Saturday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);
	
	else if (dow_read==0x06)
		sprintf(mystr,"Day:Sunday Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n",dom_read,month_read,year_read,hour_read,min_read,sec_read);
*/

sprintf(mystr,"Day:%02s Date:%02d/%02d/%02d Time: %02d:%02d:%02d\n"
,days[dow_read],dom_read,month_read,year_read,hour_read,min_read,sec_read);
	uart0_tx_str(mystr);
	delay(750);
	
	}
}	
	


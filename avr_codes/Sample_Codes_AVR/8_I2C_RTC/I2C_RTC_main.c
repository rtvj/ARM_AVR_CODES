/*******************************************************************
FileName		:	I2C_RTC_main.c
Target			:	ATmega128
Project			:	RTC READ 
Clock frequency	: 	16Mhz
Author			:	TEAM
Description		:	It receives the date and time from RTC (DS1307) and 
					send it to the serial port 
*******************************************************************/
#include "I2C_RTC_atm128.h"
#include "Serial.h"

void Initialize_RTC(void);

int main(void)
{

	static unsigned char SEC_var = 0;
	static unsigned char MIN_var = 0;
	static unsigned char HRS_var = 0;
	static unsigned char DAY_var = 0;
	static unsigned char MONTH_var = 0;
	static unsigned char YEAR_var = 0;

	volatile unsigned int dlyi;
	volatile unsigned int dlyj;
	char Debug_str[80];
	Serial_Init();

	print_string("\n\r START MAIN");
	/**************************************
	here initialization required for RTC
	**************************************/
	Initialize_RTC();	/*  this is the Intialization for RTC and writes the */

	while(1)
	{
		Update_RTC_variables();	/* this is required to getting the date and time from funcn given below */
		
		YEAR_var = RTC_getYear();
		MONTH_var = RTC_getMonth();
		DAY_var = RTC_getDay();
		HRS_var = RTC_getHour();
		MIN_var = RTC_getMinute();
		SEC_var = RTC_getSecond();

		sprintf(Debug_str,"\n\r HRS = %02d # MIN = %02d # SEC = %02d # DAY = %02d # MONTH = %02d # YEAR = %02d ",HRS_var,MIN_var,SEC_var,DAY_var,MONTH_var,YEAR_var);
		print_string(Debug_str);

		for(dlyj=0;dlyj<200;dlyj++)
			for(dlyi=0;dlyi<10000;dlyi++)
				asm("nop");
	}

}

void Initialize_RTC(void)
{
	RTC_Init();
	Write_RTC();	/* for this you need to set date and time from RTC_def_cfg.h */
}

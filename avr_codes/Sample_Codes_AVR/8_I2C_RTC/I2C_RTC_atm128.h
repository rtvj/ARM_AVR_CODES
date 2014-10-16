/*******************************************************************
FileName		:	I2C_RTC_atm128.h
Target			:	ATmega128
Project			:	RTC READ 
Author			:	TEAM
Clock frequency	: 	16Mhz
Description		:	This is library for RTC
*******************************************************************/
#ifndef _I2C_RTC_atm128_h
	#include "RTC_def_cfg.h"
	#define _I2C_RTC_atm128_h

	#include <avr/io.h>

	unsigned char READDATA[10];

	/******************  SETTING for DATE AND TIME  is in RTC_definitions.h *************************/

	void Write_RTC(void); /* for this you need to set date and time from RTC_def_cfg.h */
	void RTC_Init(void);
	void Update_RTC_variables(void);

	unsigned int RTC_getYear(void);  /* whenever you want to use call Update_RTC_variables(); */
	unsigned  char RTC_getMonth(void);  /* whenever you want to use call Update_RTC_variables(); */
	unsigned  char RTC_getDay(void);  /* whenever you want to use call Update_RTC_variables(); */
	unsigned  char RTC_getHour(void);  /* whenever you want to use call Update_RTC_variables(); */
	unsigned  char RTC_getMinute(void);  /* whenever you want to use call Update_RTC_variables(); */
	unsigned  char RTC_getSecond(void);  /* whenever you want to use call Update_RTC_variables(); */
	unsigned char conv_same_dec(unsigned char hexnumber);

	void RTC_Init(void)
	{
		/*
		I2C Freq = CPU CLK Freq/(16+2(TWBR).4^(TWPS))
		I2C Freq = 100KHZ
		CPU CLK Freq = 16MHZ
		TWPS = 0
		*/
		//TWSR = 0b11111100 initial value
		TWBR = 72;
	}

	void Write_RTC(void) /* for this you need to set date and time from RTC_def_cfg.h */
	{
		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		/* send start condition */ 

		while (!(TWCR & (1<<TWINT)));				/* wait 2 check start bit send */

		TWDR = SLAVE_ADDRESS;		/* send slave address and R/~W bit */

		TWCR = (1<<TWINT) |(1<<TWEN);	/* clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));	/* wait for ACK from Slave */

		/* 1st ACK RECVD */

		TWDR = WORD_ADDRESS;	/* send word address to slave */

		TWCR = (1<<TWINT) |(1<<TWEN);	/* clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/* wait for ACK from Slave */

		/* 2nd ACK RECVD */
		///////////////////////////////////WRITE 0X00 SEC//////////////////////////////////////////////////
		TWDR = SECONDS;								/* send data to slave to write at word address */

		TWCR = (1<<TWINT) |(1<<TWEN);				/* clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/* wait for ACK from Slave */
		//////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////WRITE 0X01 MIN//////////////////////////////////////////////////
		TWDR = MINUTES;								/* send data to slave to write at word address */

		TWCR = (1<<TWINT) |(1<<TWEN);				/* clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/* wait for ACK from Slave */
		//////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////WRITE 0X02 HRS//////////////////////////////////////////////////
		TWDR = _HOURS;								/* send data to slave to write at word address */

		TWCR = (1<<TWINT) |(1<<TWEN);				/* clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/* wait for ACK from Slave */
		//////////////////////////////////////////////////////////////////////////////////////////////////


		///////////////////////////////////WRITE 0X03 DAYOFWEEK////////////////////////////////////////////
		TWDR = DAY_OF_WEEK;							/* send data to slave to write at word address */

		TWCR = (1<<TWINT) |(1<<TWEN);				/* clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/* wait for ACK from Slave */
		//////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////WRITE 0X04 DATE/////////////////////////////////////////////////
		TWDR = DATE;								/*send data to slave to write at word address */

		TWCR = (1<<TWINT) |(1<<TWEN);				/*clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/*wait for ACK from Slave */
		//////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////WRITE 0X05 MONTH////////////////////////////////////////////////
		TWDR = MONTH;								/* send data to slave to write at word address */

		TWCR = (1<<TWINT) |(1<<TWEN);				/* clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/* wait for ACK from Slave */
		//////////////////////////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////WRITE 0X06 YEAR////////////////////////////////////////////////
		TWDR = YEAR;								/*send data to slave to write at word address */

		TWCR = (1<<TWINT) |(1<<TWEN);				/*clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/*wait for ACK from Slave */
		//////////////////////////////////////////////////////////////////////////////////////////////////


		/* 3rd ACK RECVD */

		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);		/* SEND STOP */
	}

	void Update_RTC_variables(void)
	{
		unsigned char rdptr;

		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		/* send start condition */

		while (!(TWCR & (1<<TWINT)));				/*wait 2 check start bit send */
		/*skipped check status reg for if any error */

		TWDR = 0xD0;								/*send slave address and R/~W bit */

		TWCR = (1<<TWINT) |(1<<TWEN);				/*clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/*wait for ACK from Slave */

		TWDR = 0x00;								/*send word address to slave */

		TWCR = (1<<TWINT) |(1<<TWEN);				/*clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/*wait for ACK from Slave */

		TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);		/*send start condition */

		while (!(TWCR & (1<<TWINT)));				/*wait 2 check start bit send */
		/*skipped check status reg for if any error */

		TWDR = 0xD1;								/*send slave address and R/~W bit */

		TWCR = (1<<TWINT) |(1<<TWEN);				/*clear INT for next operation and en TWI */

		while (!(TWCR & (1<<TWINT)));				/*wait for ACK from Slave */

		/****** this is dummy read  TO BE REMOVED ???BUG ***********/
		READDATA[0] = TWDR;							/*Receive Data from Slave Device */

		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);		/*send ACK for Next data to send by slave */

		while (!(TWCR & (1<<TWINT)));				/*wait for data send by Slave ???try */
		
		////////////////////////////////////////////////////////////////////////////////////////////
		for(rdptr=0;rdptr<6;rdptr++)
			{

				READDATA[rdptr] = TWDR;					/* Receive Data from Slave Device */

				TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);		/* send ACK for Next data to send by slave */
	 
				while (!(TWCR & (1<<TWINT)));		/* wait for data send by Slave ???try */
			}

		READDATA[rdptr] = TWDR;						/* Receive Next Data from Slave Device */

		////////////////////////////////////////////////////////////////////////////////////////////

		TWCR = ((1<<TWINT)|(1<<TWEN)) & (unsigned char)(~(1<<TWEA));		//Send NACK */

		while (!(TWCR & (1<<TWINT)));				/* wait for data send by Slave ???try */
		TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);	/* SEND STOP */
	}

	unsigned int RTC_getYear(void)  /* whenever you want to use call Update_RTC_variables(); */
	{
		return conv_same_dec(READDATA[6]);
	}

	unsigned  char RTC_getMonth(void) /* whenever you want to use call Update_RTC_variables(); */
	{
		return conv_same_dec(READDATA[5]);
	}

	unsigned  char RTC_getDay(void) /* whenever you want to use call Update_RTC_variables(); */
	{
		return conv_same_dec(READDATA[4]);
	}

	unsigned  char RTC_getHour(void) /* whenever you want to use call Update_RTC_variables(); */
	{
		return conv_same_dec(READDATA[2]);
	}

	unsigned  char RTC_getMinute(void) /* whenever you want to use call Update_RTC_variables(); */
	{
		return conv_same_dec(READDATA[1]);
	}

	unsigned  char RTC_getSecond(void) /* whenever you want to use call Update_RTC_variables(); */
	{
		return conv_same_dec(READDATA[0]);
	}

	unsigned char conv_same_dec(unsigned char hexnumber)
	{
		/*
		  unsigned char first_nibble = hexnumber & 0x0F,second_nibble = (hexnumber & 0xF0) >> 4; 
		  return (first_nibble + (second_nibble*10)); 
		*/
		return ((hexnumber & 0x0F) + (((hexnumber & 0xF0) >> 4)*10));
	}
#endif

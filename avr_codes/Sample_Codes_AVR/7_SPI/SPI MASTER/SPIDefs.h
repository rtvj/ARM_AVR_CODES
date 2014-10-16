/*******************************************************************
FileName		:	SPIDefs.h
Target			:	ATmega128
Project			:	Serial MASTER SPI TEST 
Clock frequency	: 	16Mhz
Description		:	this is library for SPI Master
*******************************************************************/

#ifndef _SPIDEF_h
	#define _SPIDEF_h

	#include <avr/io.h>
	 /* PIN CONFIGURATIONS FOR ATMEGA128 */
	#define DDR_SPI DDRB
	#define DD_MOSI	2	
	#define DD_SCK	1	
	#define DD_MISO	3	
	#define DD_SS	0	

	#define DDR_SS	PORTB |= 0b00010000
	#define SS_HIGH PORTB |= 0b00010000
	#define SS_LOW	PORTB &= 0b11101111


	void SPI_MasterInit(void);
	unsigned char SPI_MasterTransmit(char cData);

	void SPI_MasterInit(void)
	{
	  //Set MOSI and SCK output, all others input 
	  DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	  //Enable SPI, Master, set clock rate fck/16
	  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
	}

	unsigned char SPI_MasterTransmit(char cData)
	{
	  //Start transmission
	  SPDR = cData;
	  //Wait for transmission complete
	  while(!(SPSR & (1<<SPIF)))
		;
		return SPDR;
	}
#endif

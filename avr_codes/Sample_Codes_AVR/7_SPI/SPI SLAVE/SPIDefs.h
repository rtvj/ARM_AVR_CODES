/*******************************************************************
FileName		:	SPIDefs.h
Target			:	ATmega128
Project			:	Serial SLAVE SPI TEST 
Author			:	TEAM
Clock frequency	: 	16Mhz
Description		:	This is header file for Serial SLAVE SPI TEST 
*******************************************************************/
#ifndef _SPI_slv_def_h
#define _SPI_slv_def_h

	#include <avr/io.h>

	//PIN CONFIGURATIONS FOR ATMEGA128

	#define DDR_SPI DDRB
	#define DD_SS	0
	#define DD_MOSI	2
	#define DD_MISO	3
	#define DD_SCK	1

	void SPI_SlaveInit(void);
	char SPI_SlaveReceive(void);

	void SPI_SlaveInit(void)
	{
	  // Set MISO output, all others input
	  DDR_SPI = (1<<DD_MISO);
	  //Enable SPI
	  SPCR = (1<<SPE);
	}

	char SPI_SlaveReceive(void)
	{
	  // Wait for reception complete
	  while(!(SPSR & (1<<SPIF)))
		;
	  // Return data register
	  return SPDR;
	}
#endif

/*******************************************************************
TEST ASSIGNMENT ()

FileName		:	EEPROM_ATM128.h
Target			:	ATmega128
Project			:	ON CHIP ADC TEST 
Clock frequency	: 	16Mhz
Author			:	TEAM
Description		:	This is Library file for EEPROM
*******************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

void EEPROM_write(unsigned int uiAddress, unsigned char ucData);
unsigned char EEPROM_read(unsigned int uiAddress);
void EEPROM_WRITEFROM(unsigned char Startaddr,unsigned char Endaddr,unsigned char Sequence,unsigned char Byte);

unsigned char EEPROM_read(unsigned int uiAddress)
{
//disable the global interrupt flag

  /* Wait for completion of previous write */
  while(EECR & (1<<EEWE))
    ;
  /* Set up address register */
  EEAR = uiAddress;
  /* Start eeprom read by writing EERE */
  EECR |= (1<<EERE);

//Enable the global interrupt flag

  /* Return data from data register */
  return EEDR;
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
//disable the global interrupt flag

  /* Wait for completion of previous write */
  while(EECR & (1<<EEWE))
    ;
  /* Set up address and data registers */
  EEAR = uiAddress;
  EEDR = ucData;
  /* Write logical one to EEMWE */
  EECR |= (1<<EEMWE);
  /* Start eeprom write by setting EEWE */
  EECR |= (1<<EEWE);

//Enable the global interrupt flag
}

void EEPROM_WRITEFROM(unsigned char Startaddr,unsigned char Endaddr,unsigned char Sequence,unsigned char Byte)
{
unsigned char SeqByte =0;

	if(Startaddr>Endaddr)
		 return;

	if(!Sequence)
	{
		for(;Startaddr<Endaddr;Startaddr++)
			{
				EEPROM_write(Startaddr,Byte);	//write Byte at Addr (address Startaddress)
			}
	}
	else
	{
		for(;Startaddr<Endaddr;Startaddr++)
			{
				EEPROM_write(Startaddr,SeqByte);	//write Squence at (address Startaddress)
				SeqByte++;
				if(SeqByte == 0xFF)
					SeqByte = 0;
			}

	}
}

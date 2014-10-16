/*******************************************************************
FileName		:	EEPMtest.c
Target			:	ATmega128
Project			:	ON CHIP EEPROM TEST 
Clock frequency	: 	16Mhz
AUTHOR			:	TEAM
Description		:	This is simple test program to test the ON CHIP
					EEPROM of ATMEGA128
*******************************************************************/

#include <avr/io.h>

#include "stdio.h"

#include "EEPROM_ATM128.h"
#include "Serial.h"

int main(void)
{
	
	unsigned int addr;
	unsigned char READBYTE;
	unsigned char Mystring[30];


	Serial_Init();
	print_string("\n\rSTART OF EEPROM TEST");
	
	READBYTE = 0x00;		/* readByte variable initialized to zero */


	print_string("\n\rREADING EEPROM");			/* print to serial */

	/* performing READ FROM EEPROM */
	cli();	/* disable global interrupt */
	READBYTE = EEPROM_read(0xA);		//read Byte from address 0xa
	sei();	/* Enable global interrupt */
	
	sprintf(Mystring,"\n\rBYTE AT Address 0xA = 0x%02x",(unsigned int)READBYTE);	/* set the string to be printed on serial */
	print_string(Mystring);			/* print to serial */

	print_string("\n\rWRITING EEPROM");			/* print to serial */

	/* performing WRITE TO EEPROM */
	cli();	/* disable global interrupt	*/
	EEPROM_write(0xA,0x55);		/* write 0x55 at address 0xa */
	sei();	/* Enable global interrupt */
	

	READBYTE = 0x00;		/* readByte variable initialized to zero */

	print_string("\n\rREADING EEPROM");			/* print to serial */

	/* performing READ FROM EEPROM */
	cli();	/* disable global interrupt */
	READBYTE = EEPROM_read(0xA);		/* read Byte from address 0xa */
	sei();	/* Enable global interrupt */

	sprintf(Mystring,"\n\rBYTE AT Address 0xA = 0x%02x",(unsigned int)READBYTE);	//set the string to be printed on serial
	print_string(Mystring);			/* print to serial */

	/* reading from address 0x0000 to 0x000F */
	print_string("\n\r READING IN LOOP from address 0x0000 to 0x000F ");
		for(addr=0x0;addr<0x000F;addr++)
		{
			if(!(addr%20))
			{
				sprintf(Mystring,"\n\r0x%04d	: ",addr);
				print_string(Mystring);
			}
			sprintf(Mystring,"%02x ",(unsigned char)EEPROM_read(addr));	//write Byte at Addr (address Startaddress)
			print_string(Mystring);
		}
	
	print_string("\n\r START WRITING SEQUENCE IN LOOP from address 0x0000 to 0x000F ");

	/* writing from address 0x0000 to 0x000F */
	EEPROM_WRITEFROM(0x0000,0x000F,1,0xA5);		/* NOTE in this sequence is ON so it will start writing data as 0 1 2 3 ...*/
	//EEPROM_WRITEFROM(0x0000,0x000F,0,0xA5);	/*NOTE in this sequence is OFF so it will write data given in call */
	/* reading from address 0x0000 to 0x000F */
	for(addr=0x0;addr<0x000F;addr++)
	{
		if(!(addr%20))
		{
			sprintf(Mystring,"\n\r0x%04d	: ",addr);
			print_string(Mystring);
		}
		sprintf(Mystring,"%02x ",(unsigned char)EEPROM_read(addr));	//write Byte at Addr (address Startaddress)
		print_string(Mystring);
	}

	print_string("\n\rEND OF EEPROM TEST");

	while(1);		/* wait forever */
}

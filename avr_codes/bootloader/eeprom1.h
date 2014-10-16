#include<avr/io.h>
#include<util/delay.h>
void eeprom_write(unsigned int addr,unsigned char data)
{
	while(EECR &(1<<EEWE));// When the write access time has elapsed, the EEWE bit is cleared by hardware.
                           //The user software can poll this bit and wait for a zero before writing the next byte.		
	
	EEAR = addr; // load the address of eeprom to write
	EEDR = data; // load the data
	
	/*The EEMWE bit determines whether setting EEWE to one causes the EEPROM to be written.
When EEMWE is written to one, writing EEWE to one within four clock cycles will write data to
the EEPROM at the selected address. If EEMWE is zero, writing EEWE to one will have no
effect. When EEMWE has been written to one by software, hardware clears the bit to zero after
four clock cycles. Hence it is necessary to make EEWE bit one  within next 4 clks (security feature).*/

	EECR |= (1<<EEMWE);// set master write enable bit 
	EECR |=(1<<EEWE);// set write enable bit within next 4 clks for write strobe
}

unsigned char eeprom_read(unsigned int addr)// returning data
{
/*The user should poll the EEWE bit before starting the read operation. If a write operation is in
progress, it is neither possible to read the EEPROM, nor to change the EEAR Register.*/
	
	while(EECR &(1<<EEWE));// WAIT TILL EEWE BIT BECOME '0'	
	EEAR = addr; // load the address of eeprom to write
	EECR |=(1<<EERE);// Start eeprom read by writing EERE to '1'.
	return EEDR;
} 

void eeprom_write_string(unsigned char *addr,unsigned char *data)
{
	unsigned char i,len;
	//len=strlen(data);
	uart1_tx_num(len);
	uart1_tx_char('\n');
	//for(i=0;i<len;i++)
	while(*data != '\0')
	{
		while(EECR &(1<<EEWE));
		EEAR = *(addr+i); // load the address of eeprom to write
		EEDR = *(data+i); // load the data
		EECR |= (1<<EEMWE)&(~(1<<EEWE));// set master enable bit 
		EECR |=(1<<EEWE);// set write enable bit wit
		//addr++;data++;
		++data;
	}
	*data='\0';
}


void eeprom_read_string(unsigned char *addr,unsigned char *data)
{
	unsigned char i;
	for(i=0;i<7;i++)
	{
		while(EECR &(1<<EEWE));// WAIT TILL EEWE BIT BECOME '0'	
		EEAR = *addr; // load the address of eeprom to write
		EECR|=(1<<EERE);// Start eeprom read by writing EERE to '1'.
		*data=EEDR;
		++addr;
		++data;
	}
}

#include<avr/io.h>

#define sec 0x59 // Value to be loaded in time keepar register
#define min 0x59
#define hour 0x23
unsigned char s,m,h,mystr[30];

unsigned char convert(unsigned char);

void i2c_init()
{
	TWBR=72;// by calculation
	//TWBR=0X48;
}

void i2c_write()
{
//Transmitting start condition

	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);//TWINT flag must be cleared by software by writing a logic one to it.
                                           //clearing this flag starts the operation of the TWI.

	while(!(TWCR&(1<<TWINT)));//This bit is set by hardware when the TWI has finished its current job (Here it is to transmit start codn.) 
							   // Hence poll TWINT flag till it becomes 1.
								
	/*if((TWSR&0XF8)==0X08) // Check for successful start
	{
	uart1_tx_str("A START condition has been transmitted\n");
	}*/

//Trnsmitting slave address & 'W'+ receiving ACK

	TWDR=0xD0;// Load slv addr for write in data reg
	TWCR=(1<<TWINT)|(1<<TWEN)&(~(1<<TWSTA));// TWSTA must be cleared by software when the START condition has been transmitted.
	while(!(TWCR & (1<<TWINT)));// This insruction is repeated at each transmission,because when TWINT is set we came to know that
								// TWI has finished its current job i.e. transmission of byte
	/*if((TWSR & 0xf8)==0x18)    
	{
		uart1_tx_str("SLA+W has been transmitted;ACK has been received\n");
	}*/

//Transmitting word address to initialise RTC pointer as a data byte

	TWDR=0X00;//Load Word Address to salve(RTC)
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	/*if((TWSR&0Xf8)==0X28)
	{
	uart1_tx_str("Data byte has been transmitted; ACK has been received\n");
	}*/
	
//Transmitting sec value as a data byte
	TWDR=sec;
	TWCR=(1<<TWINT)|(1<<TWEN);

	while(!(TWCR&(1<<TWINT)));

	/*if((TWSR&0Xf8)==0X28)
	{
	uart1_tx_str("sec byte has been transmitted; ACK has been received\n");
	}*/
	
//Transmitting min value as a data byte
	TWDR=min;
	TWCR=(1<<TWINT)|(1<<TWEN);

	while(!(TWCR&(1<<TWINT)));

	/*if((TWSR&0Xf8)==0X28)
	{
	uart1_tx_str("Min byte has been transmitted; ACK has been received\n");
	}*/

//Transmitting hour value as a data byte

	TWDR=hour;
	TWCR=(1<<TWINT)|(1<<TWEN);

	while(!(TWCR&(1<<TWINT)));

	/*if((TWSR&0Xf8)==0X28)
	{
	uart1_tx_str("hour byte has been transmitted; ACK has been received\n");
	}*/

//stop condition

	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO);//Writing the TWSTO bit to one in Master mode will generate a STOP condition

	while(!(TWCR&(1<<TWSTO)));// When the STOP condition is executed on the bus, the TWSTO bit is cleared automatically.
					           //Hence, Wait for Stop bit transmission to complete: i.e TWSTO reset by h/w 
	
	//uart1_tx_str("Time successfully updated\n");
	
}

void i2c_read()
{
//Transmitting start condition

	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while(!(TWCR&(1<<TWINT)));
	/*if((TWSR&0XF8)==0X08)
	{
	uart1_tx_str("A START condition has been transmitted\n");
	}*/

//Transmitting slave address + 'R' & Receiving ACK

	TWDR=0xD0;
	TWCR=(1<<TWINT)|(1<<TWEN)&(~(1<<TWSTA));
	while(!(TWCR & (1<<TWINT)));
	/*if((TWSR & 0xf8)==0x18)
	{
		uart1_tx_str("SLA+W has been transmitted;ACK has been received\n");
	}*/

//Transmitting word address to initialise RTC pointer & Receiving ACK

	TWDR=0X00;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR&(1<<TWINT)));
	/*if((TWSR&0Xf8)==0X28)
	{
	uart1_tx_str("Data byte has been transmitted; ACK has been received\n");
	}*/
	
//Repeated start condition

	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while(!(TWCR&(1<<TWINT)));
	/*if((TWSR&0XF8)==0X10)
	{
	uart1_tx_str("A repeated START condition has been transmitted\n");
	}*/
	
//Transmitting slave address + 'R' & Recieving ACK

	TWDR=0xD1;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	/*if((TWSR & 0xf8)==0x40)
	{
		uart1_tx_str("SLA+R has been transmitted;ACK has been received\n");
	}*/

//Read data byte + Transmitting master ACK 

	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);//if data byte has been received in Master Receiver or Slave Receiver mode,
	                                      // the ACK pulse(master ACK) is generated on the TWI bus; for that TWEA bit is written to one.
										 
										 //The data in TWDR remains stable as long as TWINT is set.
										 //Hence it should be reseted by writing logic 1 to it.
	
	while(!(TWCR&(1<<TWINT)));// Wait for reception to complete of data byte

//Receiving sec value from slave + Transmitting ACK
	
	unsigned char val1,val2,val3;
	s=TWDR; //Receiving sec value from slave RTC in TWDR 
			//In Receive mode, the TWDR contains the last byte received.
	
	val1=convert(s);// BCD TO HEX Conversion
	
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);// Same as above 
	while(!(TWCR&(1<<TWINT)));
	//uart1_tx_num(val1);
	/*if((TWSR & 0xf8)==0x50)
	{
		uart1_tx_str("sec byte has been received; ACK has been transmitted\n");
	}*/

//Receiving minute value from slave	+ Transmitting ACK

	m=TWDR;// Same as above 
	val2=convert(m);
	
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	//uart1_tx_num(val2);
	/*if((TWSR & 0xf8)==0x50)
	{
		uart1_tx_str("min byte has been received; ACK has been transmitted\n");
	}*/
	
//Receiving hour value from slave + Transmitting ACK
	
	h=TWDR;// Same as above 
	val3=convert(h);
	
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while(!(TWCR&(1<<TWINT)));
	//uart1_tx_num(val3);
	/*if((TWSR & 0xf8)==0x50)
	{
		uart1_tx_str("hour byte has been received; ACK has been transmitted\n");
	}*/

	// printing & formatting on uart
	sprintf(mystr,"Real Time: %02d:%02d:%02d\n",val3,val2,val1);//inbuilt library function 
	uart1_tx_str(mystr) ;
	
}
/* The contents of the time and calendar registers of RTC are in the BCD format*/
unsigned char convert(unsigned char ch) //  Hence BCD TO HEX Conversion
  {
	return((((ch & 0xf0)>>4)*10)+(ch&0x0f));
	
  }

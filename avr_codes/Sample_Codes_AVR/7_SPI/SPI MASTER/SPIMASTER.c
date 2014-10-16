/*******************************************************************
TEST ASSIGNMENT ()

FileName		:	SPIMASTER.c
Target			:	ATmega128
Project			:	ON CHIP ADC TEST 
Author			:	TEAM
Clock frequency	: 	16Mhz
Description		:	It receives the character from the serial port 
					and sends to serial SPI Device
*******************************************************************/
#include <avr/io.h>
#include "Serial.h"
#include "SPIDefs.h"

int main(void)
{
	char RecByte = 'R';
	Serial_Init();
	SPI_MasterInit();
	DDR_SS;//set SS as output

	SS_LOW;	//SELECT THE SLAVE DEVICE
	SS_LOW;	//SELECT THE SLAVE DEVICE
	SS_LOW;	//SELECT THE SLAVE DEVICE

	print_string("\nMAIN SPI MASTER TEST\n");
	while(1)
	{
		RecByte= USART_Receive();//store the received byte
		SPI_MasterTransmit(RecByte);//send rec charac to SPI
	}
}

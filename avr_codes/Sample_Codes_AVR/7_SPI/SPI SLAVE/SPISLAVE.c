/*******************************************************************
FileName		:	SPISLAVE.c
Target			:	ATmega128
Project			:	ON CHIP ADC TEST 
Author			:	TEAM
Clock frequency	: 	16Mhz
Description		:	It receives the Byte from the serial SPI Device 
					and sends character to serial Port
*******************************************************************/
#include <avr/io.h>

#include "SPIDefs.h"
#include "Serial.h"

int main(void)
{
	char RecByte;
	Serial_Init();
	SPI_SlaveInit();
	print_string("\nSPISLAVETEST\n");
	while(1)
	{
		RecByte= SPI_SlaveReceive();	//store the received byte from the SPI dev
		USART_Transmit(RecByte);		//send rec charac to Serial port
	}
}

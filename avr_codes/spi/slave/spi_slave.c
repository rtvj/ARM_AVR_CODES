#include"uart1.h"
#include"spi_slave.h"

int main()
{
	uart1_init();
	uart1_tx_str("Slave is ready to recieve\n"); 
	spi_init();
	while(1)
	{	
	slave_rx();
	
	}
} 

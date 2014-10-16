#include"uart1.h"
#include"spi_master.h"

int main()
{
	unsigned char ch = '$';
	uart1_init();
	uart1_tx_str("Master is ready to transmit\n"); 
	spi_init();
	while(1)
	{	
	ch=uart1_rx_char() ;
	master_tx(ch);
	
	}
} 

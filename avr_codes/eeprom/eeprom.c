#include"uart1.h"
#include"eeprom.h"

int main(void)
{
	unsigned char ch;
	uart1_init();
	uart1_tx_str("Test code for EEPROM read - write operations...\n");
	//eeprom_write(0x200,'d');
	//while(1)
	//{	
		
	ch=eeprom_read(0x200);
		uart1_tx_char(ch);
	//}
}	

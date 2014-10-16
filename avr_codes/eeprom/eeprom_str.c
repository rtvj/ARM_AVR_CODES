#include<avr/io.h>
#include"uart1.h"
#include<util/delay.h>
#include"eeprom.h"


int main(void)
{    unsigned char str[]= "Rutvij";
     unsigned char mystr[6],data;
     uart1_init();
     uart1_tx_str("uart has initialized...\n");
     eeprom_write(0x100,'A');
     data= eeprom_read(0x100);
	 uart1_tx_char(data);uart1_tx_char('\n');
/*while(*(data1)!='\0')
    {
     eeprom_write(*(address++),*(data1));
    } 
    *(address)='\0';

  while(*(address)!='\0')
     {
     data=eeprom_read(*address++);
     uart1_tx_char(data);
     }*/
	//eeprom_write_string(0x200,str);
    eeprom_read_string(0x200,mystr); 
	uart1_tx_str(mystr);
     //while(1);
     


}

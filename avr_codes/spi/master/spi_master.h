#include<util/delay.h>
void spi_init()
{
	DDRB|=(1<<0)|(1<<1)|(1<<2);
	DDRB&=~(1<<3);//MOSI,SCLK,SS as o/p MISO as i/p
	PORTB|=(1<<3);// enable pull-up for MISO
	SPCR = 0X73;// master,lsb,first,fosc/128,cpol=cpha=0
	PORTB|=(1<<0); // SS=1........SLAVE Reset
}

void master_tx(unsigned char data)
{
		
	PORTB&=~(1<<0);// ss=0.......slave select 
	SPDR = data;	
	while(!(SPSR&(1<<SPIF)));
	//_delay_ms(10);
	uart1_tx_char(SPDR);
	//_delay_ms(10);
	
}

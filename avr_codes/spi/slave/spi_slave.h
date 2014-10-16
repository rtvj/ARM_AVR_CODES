#include<util/delay.h>
spi_init()
{
	DDRB&=~((1<<0)|(1<<1)|(1<<2));//MOSI,SCLK,SS as i/p 
	DDRB|=(1<<3);//MISO as o/p
	PORTB|=(1<<0)|(1<<1)|(1<<2);// enable pull-up for MOSI,SCLK,SS 
	SPCR = 0X63;// slave,lsb,first,fosc/128,cpol=cpha=0
	SPDR='$'; //default value .......for test
}

void slave_rx()
{	
	while(!(SPSR&(1<<SPIF)));
	uart1_tx_char(SPDR);
	_delay_ms(10);
	
}

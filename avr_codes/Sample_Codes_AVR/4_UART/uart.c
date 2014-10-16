#include<avr/io.h>
#include<util/delay.h>

int main(void)
{

UBRR1L = 103;
UBRR1H = 0;

UCSR1B = 0X18;
UCSR1C = 0X86;

unsigned char a,b,c;

a = b = c = 0;
a = 11;
b = 0;
c = a/b;
	while(1)
	{
		while(!(UCSR1A & (1<<UDRE)));
		UDR1 = c + 0x30;
		_delay_ms(1000);
		
	}

}

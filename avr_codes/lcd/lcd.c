#include<avr/io.h>
#include<util/delay.h>
#include"LCD_mega128.h"
int main(void)
{
	lcd_init();
	while(1)
	{	
	lcd_char('A');	
	WaitMs(1000);
	lcd_cmd(0x01);
	lcd_char('A');
	}	
}

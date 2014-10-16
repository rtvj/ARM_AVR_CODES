#include <avr/io.h>
#include "LCD_mega128.h"

int main(void)
{
	int a=1,b=1,c;
	
	lcd_init();
	
	c=a+b;
	
	lcd_gotoxy1(0);
	
	lcd_showvalue(c);
}	
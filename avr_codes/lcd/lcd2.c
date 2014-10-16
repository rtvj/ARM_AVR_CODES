#include<avr/io.h>
#include<util/delay.h>
#include"LCD_mega128.h"
int main(void)
{	int i;
	unsigned char a[8]={0x00,0x0A,0X00,0X04,0X00,0X0A,0X04,0X00};	
	lcd_init();
	//lcd_cmd(0x48);		//set the address of the CGRAM
	/*for(i=0;i<8;i++)
	{
	lcd_putchar(a[i]);		//put the user generated pattern into the CGRAM
	}*/
	lcd_cmd(0x01);
	_delay_ms(500);
	lcd_cmd(LINE1);
	lcd_putchar(1);			// puts the generated character on the display
	lcd_cmd(0x0c);
	_delay_ms(500);
	lcd_cmd(0x50);
	for(i=0;i<8;i++)
	{
	lcd_putchar(a[i]);
	}
	//lcd_cmd(0x01);
	_delay_ms(500);
	lcd_cmd(LINE2);
	//lcd_cmd(0x40);
	lcd_putchar(48);//
	lcd_putchar(0);
	lcd_putchar(1);
	lcd_putchar(2);
	lcd_cmd(0x01);
	lcd_putchar('A');
	lcd_string("This is a test");

}

























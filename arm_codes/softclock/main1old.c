/*Testing ADC on sinusoidal signal
name : sanjay
date : 11/3/12
compiler : avr_gcc
environment: linux
*/
//#include"usart1.h"
 #include"lcd_2148old.h"
//#include"usart0.h"
#include"startup.h"
//#include<util/delay.h>


int main(void)
{
//unsigned char i,a[8]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};
//char j = 0;
sys_init(); // system initialisation
lcd2148_init();
lcd_gotoxy1(1);
lcd2148_data("abcd"); 
lcd_gotoxy2(1);
lcd2148_data('B'); 

/*
lcd_cmd(0x40);
while(1) 
{
for(i=0;i<8;i++)
{
//lcd_putchar(a[i]);
lcd_gotoxy1(a[i]);
}
lcd_cmd(0x01);
_delay_ms(600);
//lcd_cmd(LINE1);
//_delay_ms(600);
//lcd_cmd(LINE2);
//lcd_putchar(0);
//return 0;
}
*/
}





 





#include"uart1.h"
#include<util/delay.h>
//#include"LCD_mega128.h"
#include"ldr_poll.h"
int main(void)
{
ldr_init();

uart1_init();
uart1_tx_str("uart has initialised....\n");

/*lcd_init();
lcd_putchar('A');*/

while(1)
    {
		ldr_read();
    }
}    

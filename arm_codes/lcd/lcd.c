#include"startup.h"
#include"LPC214x.h"
#include"lcd_2148.h"
int main()
{
	/*lcd2148_init();
	lcd2148_data('A');
	lcd2148_init();
	lcd2148_gotoxy2(1);
	lcd2148_data('A');*/
	lcd2148_init();
	lcd2148_string("nikhil");
}

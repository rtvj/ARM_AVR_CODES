#include"uart1.h"
#include"joystick.h"
char endianess() {
  
  int i = 0X0001;
  char *b;
  b = (char *)&i;
  if(*b == 1)
    return 1;
  if(*b == 0)
    return 0;
  
}
int main()
{
	uart1_init() ;
	/*while(1)
	{	
	//uart1_tx_str("x_axis\t y_axis\n") ;
	y_axis();
	uart1_tx_str("\t");
	x_axis();
	uart1_tx_str("\n\r") ;
	}
	*/
	if(endianess() == 1)
	  uart1_tx_str("AVR is little endian\n\r");
	if(endianess() == 0)
	  uart1_tx_str("AVR is big endian\n\r");
	
}

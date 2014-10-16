#include"startup.h"
#include"LPC214x.h"

int main()
{	unsigned int i,j;
	sys_init();//for pll
	PINSEL0&=~(1<<22);// Pins P1.25-16 are used as GPIO pins.
	PINSEL0&=~(1<<23);
	IODIR0|=(1<<11);//AS O/P
	while(1)
	{
	IOSET0|=(1<<11);
	for(i=0;i<5500;i++){
		for(j=0;j<5500;j++);}
	IOCLR0|=(1<<11);
	for(i=0;i<5500;i++){
		for(j=0;j<5500;j++);}	
	}
}	
	


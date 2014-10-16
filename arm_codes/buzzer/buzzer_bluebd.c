#include"startup.h"
#include"LPC214x.h"

int main()
{	unsigned int i,j;
	sys_init();//for pll
	PINSEL2&=~(1<<3);// Pins P1.25-16 are used as GPIO pins.

	IODIR1|=(1<<25);//AS O/P
	while(1)
	{
	IOSET1|=(1<<25);
	for(i=0;i<5500;i++){
		for(j=0;j<55000;j++);}
	IOCLR1|=(1<<25);
	for(i=0;i<5500;i++){
		for(j=0;j<55000;j++);}	
	}
}	
	


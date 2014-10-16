#include"startup.h"
#include"LPC214x.h"

int main()
{	unsigned int i,j;
	sys_init();//for pll
	PINSEL0&=~((1<<30)|(1<<31)|(1<<22)|(1<<23));//
	IODIR0|=(1<<11);//AS O/P
	IODIR0&=~(1<<15);//AS i/P
	IOPIN0=0xff;
	while(1)
	{
		if((IOPIN0&(1<<15)))	//if s/w is pressed pin value is 1
		{
			IOSET0|=(1<<11);
		}
		else
		IOCLR0|=(1<<11);
	}
}	
	


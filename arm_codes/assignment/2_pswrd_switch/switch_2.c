#include<stdio.h>
#include"startup.h"
#include"LPC214x.h"
#include"uart.h"

int main()
{	unsigned int i,j,count;
	unsigned char str1[]="nikhil"; 
 	unsigned char str2[6];
	sys_init();//for pll
	uart0_init();
	PINSEL0&=~((1<<30)|(1<<31)|(1<<22)|(1<<23));//
	//IODIR0|=(1<<11);//AS O/P
	IODIR0&=~(1<<15);//AS i/P
	//IOPIN0=0xff;
	
	while(1)
	{
		if(!(IOPIN0&(1<<15)))	//if s/w1 is pressed pin value is 1
		{
			uart0_tx_str("Enter Passward\n"); 
			uart0_rx_str(str2);
			count=strcmp(str1,str2);
 			if (count==0)
 				uart0_tx_str("Valid Password\n"); 
   				//IOCLR0|=(1<<11);}
 			else
 				uart0_tx_str("Non-Valid Password\n"); 
    				//IOSET0|=(1<<11);
		}
	}
}	
	


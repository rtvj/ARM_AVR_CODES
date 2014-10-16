#include"startup.h"
#include"VIClowlevel.h"
#include"uart0.h"
#include"lcd_2148old.h"
#include"timer.h"

volatile unsigned char sec ,min,hr,mystr[30];

void EXT2_ISR(void) __attribute__ ((interrupt("IRQ")));

int main(void)
{
	sys_init();
	timer_init();
	lcd2148_init();
	PINSEL0|=(1<<31)&(~(1<<30));
	EXTMODE|=(1<<2);
	EXTPOLAR&=~(1<<2);
	EXTINT=(1<<2);
	VICIntSelect&=~(1<<16);
	VICIntEnable|=(1<<16);                     //enable IRQ
	VICVectCntl0|=(1<<5)|(1<<4);               //assigning slot and enabling IRQ slot
    VICVectAddr0=(unsigned int)EXT2_ISR;      //load vector address
    
    uart0_init(9600);
    uart0_tx_string("in main program....\n");
    enableIRQ();
    while(1);
}

void EXT2_ISR(void)
{
	unsigned int i,j;
	uart0_tx_string("switch is press....");
		
		  while(1)
{
uart0_tx_string("stage1....");
  while(!(T0IR&(1<<0)));  //wait till MR0 interrupt occurs
  uart0_tx_string("stage2..");
  T0IR=(1<<0);
    sec++;
 if(sec>59)
    {
     sec=0;    //1 min elapsed
     min++;   
    }
    if(min>59)
    {
     min=0;
     hr++;
    }  
    if(hr>23)
    {
     hr=0;
    }
    lcd_gotoxy1(1); 
    lcd_showvalue(hr);
   lcd2148_data(':');
    lcd_showvalue(min);
    lcd2148_data(':');
    lcd_showvalue(sec);
    
    sprintf(mystr,"%02d:1%02d:%02d\n",hr,min,sec);  
   // lcd2148_data(mystr);
   // uart0_tx_string(mystr);
}
		EXTINT|=(1<<2);                            //flag clear
		VICVectAddr=0x00;
}

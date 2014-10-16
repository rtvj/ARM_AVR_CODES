/****************************************************************
Name		: lcd_2148.c
Description	: Library for JHD162A (HD44780) on lpc2148
date modified :	7th Apr 2010
Author		: Aditya
*****************************************************************/

//#include"LPC214x.h"

void timer_init(void)
{

T0TCR|=(1<<1);  //reset TC,PC
T0CTCR = 0x00; //slect timer mode
T0PR =60;  //for 1 sec delay
T0MR0 =1000000;
T0MCR=0x3;//generate interrupt on match 7 reset TC to 00
T0TCR=0x1;  //start the timer
}



/*******************Priority Inversion Problem while using Semaphore************************/
/* Author: NIKHIL
   DATE : 22/05/2012

*/ 
#include "includes.h"
#include "uart1.h"
#include <util/delay.h>

OS_STK task1_stack[256];
OS_STK task2_stack[128];
OS_STK task3_stack[256];

OS_EVENT *sem;

volatile INT8U err;

void task1(void *data);
void task2(void *data);
void task3(void *data);

int main()
{
	
	OSInit();
	uart1_init();
	DDRC=0xFF;
	PORTC=0xFF;
	
	err = OSTaskCreate(task1,(void*)0,&task1_stack[255],1);
	if(err==OS_NO_ERR)
	{

		uart1_tx_str("Task 1 has been successfully created...\n\r");
	}
	
	err = OSTaskCreate(task2,(void*)0,&task2_stack[127],2);
	if(err==OS_NO_ERR)
	{

		uart1_tx_str("Task 2 has been successfully created...\n\r");
	}
	
	err = OSTaskCreate(task3,(void*)0,&task3_stack[255],3);
	if(err==OS_NO_ERR)
	{

		uart1_tx_str("Task 3 has been successfully created...\n\r");
	}

        sem = OSSemCreate(0);        
        OSStart();			//present in core.c
}


void task1(void *data1)
{
	while(1)
	{
        OSSemPend(sem,0,&err);
        uart1_tx_str("Task 1\t");
	uart1_tx_str("Priority...");
	uart1_tx_num(OSPrioCur);//Displays current priority
	uart1_tx_str("\n");
	}
}

void task2(void *data2)
{
	while(1)
        { 
		OSTimeDly(1);
                PORTC=0x00;
                OSTimeDly(1);
                PORTC=0xFF;
        }
}

void task3(void *data3)
{
	while(1)
	{
        uart1_tx_str("Task 3\t");
	 uart1_tx_str("Priority...");
	uart1_tx_num(OSPrioCur);//Displays current priority
	 uart1_tx_str("\n");
        OSSemPost(sem);
   	 }
}
/* o/p :

Task 3  Priority...3     
Task 1  Priority...1

first executes task 3,hence priority inversion
*/

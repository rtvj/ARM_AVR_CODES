/**************************Priority Inheritance by using mutex**************************** */
/* Author : Nikhil
   Date :  22/05/2012
*/

#include "includes.h"
#include "uart1.h"
#include <util/delay.h>

OS_STK task1_stack[256];
OS_STK task2_stack[128];
OS_STK task3_stack[256];


OS_EVENT *mutex;

volatile INT8U err;


void task1(void *data);
void task2(void *data);
void task3(void *data);


void timerinit()
{
	TCNT0=0;
	TCCR0=0X07;//prescalar of fosc/1024
	TIMSK |=(1<<0);// Enable TOV
}
int main()
{
	
	OSInit();
	uart1_init();
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
	
	

	mutex = OSMutexCreate(0,&err);
    	
	OSStart();			//present in core.c

}

void task1(void *data1)

{	OS_ENTER_CRITICAL(); /* Disable interrupts - OS_cpu.h*/
	timerinit();
	OS_EXIT_CRITICAL();/* Enable interrupts */
	
	INT8U string[20];
	while(1)
	{
	OSTimeDly(6);
       	OSMutexPend(mutex,0,&err);
	if(err==OS_NO_ERR)
	{
	uart1_tx_str("Mutex 1 Aquired\n\r");
	uart1_tx_str("Task 1 priority raised to");
	uart1_tx_num(OSPrioCur);
	uart1_tx_str("\n\r");
	uart1_tx_str("All\n\r");
	//sprintf(string,"Task 1 priority raised to %d\n",OSPrioCur);
	
	}
	
	err = OSMutexPost(mutex);
	if(err==OS_NO_ERR)
	{
	uart1_tx_str("Mutex 1 Released \n\r");
	//OSTimeDly(3);
	}
}
}

void task2(void *data2)
{
while(1)
        {
               	uart1_tx_str("In Task 2\n\r");
				_delay_ms(1000);
				//OSTimeDly(1);
                PORTC=0x00;
                _delay_ms(1000);
				//OSTimeDly(1);
                PORTC=0xFF;
               OSTimeDly(3);
                
        }
      
}

void task3(void *data3)
{	INT8U string[20];
	while(1)
	{
	
       	OSMutexPend(mutex,0,&err);
	if(err==OS_NO_ERR)
	{
	uart1_tx_str("Mutex 3 Aquired\n\r");
	uart1_tx_str("Task 3 priority raised to");
	uart1_tx_num(OSPrioCur);
	uart1_tx_str("\n\r");
	uart1_tx_str("Hello\n\r");
	
	//sprintf(string,"Task 3 priority raised to %d\n",OS_PRIO_SELF);
	//uart1_tx_str(string);
	}
	
	err = OSMutexPost(mutex);
	if(err==OS_NO_ERR)
	{
	uart1_tx_str("Mutex 3 Released \n\r");
	OSTimeDly(1);
	}
}
}


/* o/p :
In Task 2.............will be in the running state after specific time 
Mutex 1 Aquired
Task 1 priority raised to1
All
Mutex 1 Released
In Task 2
Mutex 3 Aquired.......Meanwhile,Task 1 tries to access resource,hence priority of task 3
                      is raised to 0 (priority inheritance) 
Task 3 priority raised to0
Hello
Mutex 3 Released
In Task 2
....
....
*/

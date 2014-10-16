#include <util/delay.h>
//#include <avr/io.h>
#include "uart1.h"
#include<avr/interrupt.h>
#include "adc.h"


int mdata;
char ldata;
int main(void) {
  
  adc1_init();
  uart1_init();
  sei();
  DDRA |= (1<<PA3);
    
  while(1){
    
    //uart1_tx_str("I am in while !! \n\r");
  }//{

  return 0;
}

ISR(ADC_vect){

    //ADCSRA |= (1<<ADSC);
    //data = ldr_read();
    mdata = ADCH;
    //ldata = ADCL;
    //mdata |= (mdata<<8) | ldata;
    
    uart1_tx_num(mdata);
    uart1_tx_str("\n\r");
    //_delay_ms(10);
    
    if(mdata > 50) {
      
      PORTA |= (1<<PA3);
      
    }
    else{
    PORTA &= ~(1<<PA3);
    }
    ADCSRA |= (1<<ADSC);
  //}
  //return 0;
}

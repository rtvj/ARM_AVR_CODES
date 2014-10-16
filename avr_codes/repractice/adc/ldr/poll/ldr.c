#include <avr/io.h>
#include "uart1.h"
#include "adc.h"
#include <util/delay.h>

int main(void) {
  
  int data;
  adc1_init();
  uart1_init();
  while(1) {
    
    data = ldr_read();
    uart1_tx_num(data);
    uart1_tx_str("\n\r");
    _delay_ms(10);
    
  }
  return 0;
  
}
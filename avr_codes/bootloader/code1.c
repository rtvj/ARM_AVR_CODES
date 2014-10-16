//#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/boot.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <avr/eeprom.h>
#include "uart1.h"
#include "LCD_mega128.h"
#include "eeprom1.h"

int main ( void )
{
  uint16_t i;
  uint8_t A [ 512 ];
  uint8_t sreg;
  uint32_t page = 0;
  uint16_t w;
  unsigned char *buf = A;
  volatile int j = 4;
  
  //====================================================================================
  lcd_init();	// initialization of LCD
  
  lcd_cmd(0x01);
  lcd_cmd(LINE1);
  lcd_string("CUSTOM");
  lcd_cmd(LINE2);
  lcd_string("BOOTLOADER PROJECT");
  _delay_ms(3000);
  
  lcd_cmd(0x01);
  lcd_cmd(LINE1);
  lcd_string("Booting ATMEGA64");
  _delay_ms(2000);
  
  lcd_cmd(0x01);
  lcd_cmd(LINE1);
  lcd_string("LCD[OK]");
  lcd_cmd(LINE2);
  lcd_string("16*2,4 bit");
  _delay_ms(2000);
  
  uart1_init(); // initialization of UART
  
  lcd_cmd(0x01);
  lcd_cmd(LINE1);
  lcd_string("UART1[OK]"  );
  lcd_cmd(LINE2);
  lcd_string("9600bps,Tx&Rx");
  _delay_ms(2000);
  
  lcd_cmd(0x01);
  lcd_cmd(LINE1);
  lcd_string("loading App...");
  lcd_cmd(LINE2);
  for(i = 0; i < 16; i ++)
  {
    _delay_ms(350);
    lcd_putchar(0xFF);
  }
  
  lcd_cmd(0x01);
  lcd_cmd(LINE1);
  //====================================================================================
  
  
  //################################ BOOTING FROM EEPROM ###############################//
  for ( i = 0; i < 512; i ++ )
    A [ i ] = eeprom_read(/*(const uint8_t *)*/i); 
  
  while(1)
  {
    //==========================================================================//
    if(j)
    {
      // Disable interrupts.
      sreg = SREG;
      cli();
      eeprom_busy_wait ();
      boot_page_erase (page);
      boot_spm_busy_wait ();      // Wait until the memory is erased.
      
      for (i=0; i<SPM_PAGESIZE; i+=2)
      {
	// Set up little-endian word.
	w = *buf++;
	w += (*buf++) << 8;
	
	boot_page_fill (page + i, w);
      }
      boot_page_write (page);     // Store buffer in flash page.
      boot_spm_busy_wait();       // Wait until the memory is written.
      boot_rww_enable ();
      SREG = sreg;
    }
    else
    {
      asm ( "jmp 0x0000" );
    }
    
    j--;
    page = page + 128;
    //==============================================================================//
  }
  //################################ BOOTING FROM EEPROM ###############################//
  
}


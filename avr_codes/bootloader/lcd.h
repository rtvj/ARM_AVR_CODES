//#################### LCD #########################//

#define _LCD_H

#ifndef F_CPU
#define F_CPU 8000000
#endif

#include<avr/io.h>
#include<util/delay.h>
#include<inttypes.h>
#define rs PA0
#define rw PA1
#define en PA2
void lcd_init();
void dis_cmd(char);
void dis_data(char);
void lcdcmd(char);
void lcddata(char);
void lcd_clear(void);
void lcd_2nd_line(void);
void lcd_1st_line(void);
void lcd_string(const char *data);

void lcd_string(const char *data)
{
  for(;*data;data++)
    dis_data (*data);
}

void lcd_clear(void)
{
  dis_cmd(0x01);
  _delay_ms(10);
}

void lcd_2nd_line(void)
{
  dis_cmd(0xC0);
  _delay_ms(1);
}

void lcd_1st_line(void)
{
  dis_cmd(0x80);
  _delay_ms(1);
}

void lcd_init() // fuction for intialize 
{
  DDRA=0xFF;
  dis_cmd(0x02); // to initialize LCD in 4-bit mode.
  dis_cmd(0x28); //to initialize LCD in 2 lines, 5X7 dots and 4bit mode.
  dis_cmd(0x0C);
  dis_cmd(0x06);
  dis_cmd(0x80);
  dis_cmd(0x01);
  _delay_ms(10);
}

void dis_cmd(char cmd_value)
{
  char cmd_value1;
  cmd_value1 = cmd_value & 0xF0; //mask lower nibble because PA4-PA7 pins are used. 
  lcdcmd(cmd_value1); // send to LCD
  
  cmd_value1 = ((cmd_value<<4) & 0xF0); //shift 4-bit and mask
  lcdcmd(cmd_value1); // send to LCD
}


void dis_data(char data_value)
{
  char data_value1;
  data_value1=data_value&0xF0;
  lcddata(data_value1);
  
  data_value1=((data_value<<4)&0xF0);
  lcddata(data_value1);
}

void lcdcmd(char cmdout)
{
  PORTA=cmdout;
  PORTA&=~(1<<rs);
  PORTA&=~(1<<rw);
  PORTA|=(1<<en);
  _delay_ms(1);
  PORTA&=~(1<<en);
}

void lcddata(char dataout)
{
  PORTA=dataout;
  PORTA|=(1<<rs);
  PORTA&=~(1<<rw);
  PORTA|=(1<<en);
  _delay_ms(1);
  PORTA&=~(1<<en);
}

#endif
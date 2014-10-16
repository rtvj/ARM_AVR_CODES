/****************************************************************************************
FileName		:	LCD_mega128.h
ProjectName		:	LCD TEST 
Target			:	ATmega128
CPU Clock		:	16Mhz
Author			:	TEAM
Description		:	This is a header file for LCD.
****************************************************************************************/
/*	LCD.h
*
*	This header files have implementation of some common functions of the LCD.
*	Include this header file in your C code. Call the lcd_init() function before
	calling any other functions to initialize the lcd.


	lcd_init() ----- Call the lcd_init() function before calling any other functions
			  to initialize the lcd.
	lcd_cmd() ------ This function is used to give any command instructions to the
			  LCD. For e.g lcd_cmd(0x01) will give the clear command.
	lcd_char() ----- This function will display a single character on the LCD display.
			  For example lcd_char(0x61) will display A. Again lcd_char('b')
			  will display b.
	lcd_string()---- This function will display a string. An example of this would be
			  like lcd_string("This is AVR")
	lcd_showvalue()- This will show a 3-digit decimal value on the LCD. For example if
			  we give lcd_showvalue(0xFF) then 255 will be displayed.
	lcd_gotoxy1()--- Will set the cursor at a particular position on LINE1 of the LCD.
			  So lcd_gotoxy1(3) will set the cursor at the 3+1=4th column in
			  the 1st line of the LCD.
	lcd_gotoxy2()--- Will set the cursor at a particular position on LINE2 of the LCD.
			  So lcd_gotoxy2(0) will set the cursor at the 0+1=1st column in
			  the 2nd line of the LCD.

	lcd_exit() ----- You may call this function after you are over with your LCD.While
			  calling the lcd functions, there would be some changes to the
			  PORTA. This restores the original PORTC configuration before
			  calling the lcd_init() function. This is not absolutely necessary.
			  You may or may not use this function.
*
*
*
*/

#define _LCD_MEGA128_INCLUDED_

#define BIT(x)	(1 << (x))
#define CHECKBIT(x,b) (x&b)		//Checks bit status
#define SETBIT(x,b) x|=b;		//Sets the particular bit
#define CLEARBIT(x,b) x&=~b;	//Clears the particular bit
#define TOGGLEBIT(x,b) x^=b;	//Toggles the particular bit


#define LINE1	0x80
#define LINE2	0xC0

#define PORTUSED PORTA
#define DDRUSED DDRA

unsigned char k=0,j=0;
unsigned char save=0;

void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void toggleE(void);
void dely_ns(unsigned char tim);
void lcd_char(unsigned char single);
void lcd_string(unsigned char str[32]);
void lcd_showvalue(unsigned char num);
void lcd_gotoxy1(unsigned char pos);
void lcd_gotoxy2(unsigned char pos);
void lcd_exit(void);
void WaitMs(unsigned int ms);


void lcd_init(void)	//init the lcd
{	
	save=PORTUSED;
	DDRUSED=0xFF;//set the direction of port pins as o/p
	WaitMs(15);// After power up,wait about 15ms before sending initializing commands to LCD.
	CLEARBIT(PORTUSED,BIT(0)+BIT(1)+BIT(2));//RS=0(PA.0) means COmmand/Instruction reg selected & E=0(PA.2) before sending any data.
	PORTUSED=0x20;// 4 bit mode selected (Datasheet-pg 24-Table 6-Function Mode or Refer Notebk)) 
	lcd_cmd(0x02);  // Cmd for returning home
	lcd_cmd(0x01);// Cmd for clear display
	lcd_cmd(0x0F);// Cmd for Display on, cursor blinking
	lcd_cmd(0x02);// Cmd for returning home
	lcd_cmd(LINE1);// selects the cursor to first line first location
	WaitMs(15);
		
}

void toggleE(void) // High to Low pulse to pin E(Enable) to enable internal latch of LCD
{                  // (After sending any data to the LCD.)
SETBIT(PORTUSED,BIT(2)); // High pulse to pin E(Enable)
dely_ns(250);            // Pulse width
CLEARBIT(PORTUSED,BIT(2));//Low pulse to pin E(Enable)
}

void dely_ns(unsigned char tim)
{
	for(j=0;j<tim;j++)
	{
		for(k=0;k<10;k++)
		{};
	}
}

void lcd_cmd(unsigned char cmd) // To send any command to the LCD (Refer Notebk)
{
	CLEARBIT(PORTUSED,BIT(0)+BIT(1)+BIT(2));// Same as above
	PORTUSED=((cmd&0xF0));		//To send higher nibble 1st		
	toggleE();// After sending any data to the LCD
	PORTUSED=(((cmd&(0x0F))*16));	//Then to send lower nibble
	toggleE();// Same as above
}

void lcd_putchar(unsigned char sig)// To display a single character on the LCD.
{
		//PORTUSED=0x01; // Not necessary
		CLEARBIT(PORTUSED,BIT(0)+BIT(2));// Same as above
		PORTUSED=(sig&0xF0)|0x01;// To send data(higher nibble) to LCD,make data register RS=1(Refer Notebk)			
		toggleE();
		PORTUSED=((sig&(0x0F))*16)|0x01;//to send lower nibble with RS=1
		toggleE();
}

void lcd_char(unsigned char single)
{
	int i;
	if(single =='\t')
	{
		for(i =0 ; i<2 ; i++)
		{	
		lcd_putchar(' ');
		}
	}
	else if(single=='\n')
	{
		lcd_gotoxy2(0);	
	}
	else 
	{
		lcd_putchar(single);
	}
}

void lcd_string(unsigned char str[32])
{
	unsigned char k=0;
	//PORTUSED=0x01;// Not necessary
	CLEARBIT(PORTUSED,BIT(0)+BIT(2));
	while(str[k]!='\0')	//Till null character is encountered
		{
			if(k==16) // As LCD is 16x2
				lcd_cmd(LINE2);// go to the LINE 2
			PORTUSED=((str[k])&0xF0)|0x01;//To send higher nibble 1st	with RS=1
			toggleE();
			PORTUSED=((str[k]&(0x0F))*16)|0x01;//Then to send lower nibble with RS=1
			toggleE();
			k++;
		}
}


void lcd_showvalue(unsigned char num)	//prints the decimal 3 digit value of num
{
	unsigned char H=0,T=0,O=0;
	H=num/100;//calculating 100th place no. by dividing by 100
	T=(num - (H*100))/10;//calculating 10th place no. by substracting 100th place no.& then 2 digit no. divided by 10
	O=(num - (H*100) - (T*10));//calculating unit place no.by substracting 100th place & 10th place no.
	
	lcd_char(H+48);//Sending ASCII values
	lcd_char(T+48);
	lcd_char(O+48);
}

void lcd_gotoxy1(unsigned char pos)
{
	lcd_cmd(LINE1+pos);
}

void lcd_gotoxy2(unsigned char pos)
{
	lcd_cmd(LINE2+pos);
}
		

void lcd_exit(void)
{
	PORTUSED=save;
}

/* waits (pauses) for ms milliseconds (assumes clock at 16MHz) */
void WaitMs(unsigned int ms)
{
	int i;

	while (ms-- > 0)
	{
		/* 16380 (16k) clock cycles for 1ms; each time through loop
		   is 5 cycles (for loop control + nop) */
		for (i = 0; i < 3276; ++i)
			asm("nop");
	}
}


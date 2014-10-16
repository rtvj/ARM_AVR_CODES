#define LINE1	0x80
#define LINE2	0xC0

void delay(unsigned int i)
{
	volatile unsigned int j=0,k = 0;
	for (j=0;j<i;j++)
		for (k=0;k<6000;k++);	// 
}

void latch(void)
{
	delay(10);
	IOSET0 |= (1 << 18);	// LCD_EN = 1
	delay(10);
	IOCLR0 |= (1 << 18);
}

void lcd2148_cmd(unsigned char cmd)
{
	IOCLR0 |= (1 << 16);		// RS = 0, command

	IOCLR0 |= (0x0f << 19);
	IOSET0 |= ((cmd & 0xf0) << 15);	// write higher nibble first
	latch();

	IOCLR0 |= (0x0f << 19);
	IOSET0 |= ((cmd & 0x0f) << 19);	// write lower nibble
	latch();
}



void lcd2148_init(void)
{
	sys_init();//for pll
	PINSEL1&=~((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)|(1<<5)|(1<<6)|(1<<7)|(1<<8)|(1<<9)|(1<<10)|(1<<11)|(1<<12)|(1<<13));
	IODIR0|=(1<<16)|(1<<17)|(1<<18)|(1<<19)|(1<<20)|(1<<21)|(1<<22);//AS O/P
	IOCLR0 |= 0x00007F00;
	
	delay(100);
	IOCLR0 |= (0xf << 19);
	IOSET0 |= (3 << 19);		// cmd(0x30)
	latch();

	delay(5);
	IOCLR0 |= (0xf << 19);
	IOSET0 |= (3 << 19);		// cmd(0x30)
	latch();
	
	delay(1);
	IOCLR0 |= (0xf << 19);
	IOSET0 |= (3 << 19);		// cmd(0x30)
	latch();

	IOCLR0 |= (0xf << 19);
	IOSET0 |= (2 << 19);		// cmd(0x20), 4-bit mode
	latch();					// LCD_EN pulse
	
	lcd2148_cmd(0x28);			// 2 line display, 5x8 display
	lcd2148_cmd(0x0f);			// display ON, cursor ON, blink ON
	lcd2148_cmd(0x01);			// clear display
	lcd2148_cmd(0x02);			// cursor home
	lcd2148_cmd(0x06);			// increment cursor by 1, no shift
}
void lcd2148_data(unsigned char data)
{
	IOSET0 |= (1 << 16);		// RS = 1, data

	IOCLR0 |= (0x0f << 19);
	IOSET0 |= ((data & 0xf0) << 15);	// write higher nibble first
	latch();

	IOCLR0 |= (0x0f << 19);
	IOSET0 |= ((data & 0x0f) << 19);	// write lower nibble
	latch();
}
void lcd2148_string(unsigned char str[32])
{
	unsigned char k=0;

	IOCLR0 |= ((1 << 16)|(1 << 17)|(1 << 18));	
	while(str[k]!='\0')	//Till null character is encountered
		{
			if(k==16) // As LCD is 16x2
				lcd2148_cmd(LINE2);// go to the LINE 2

			IOSET0 |= (1 << 16);	// RS = 1, data
			IOCLR0 |= (0x0f << 19);
			IOSET0 |= ((str[k]& 0xf0) << 15);	// write higher nibble first
			latch();
			IOSET0 |= (1 << 16);// RS = 1, data
			IOCLR0 |= (0x0f << 19);
			IOSET0 |= ((str[k] & 0x0f) << 19);	// write lower nibble
			latch();
			
			k++;
		}
}
/*
voT=(num - (H*100))/10;id lcd2148_showvalue(unsigned char num)	//prints the decimal 3 digit value of num
{
	unsigned char H=0,T=0,O=0;
	H=num/100;//calculating 100th place no. by dividing by 100
	T=(num - (H*100))/10;//calculating 10th place no. by substracting 100th place no.& then 2 digit no. divided by 10
	O=(num - (H*100) - (T*10));//calculating unit place no.by substracting 100th place & 10th place no.
	
	lcd2148_data(H+48);//Sending ASCII values
	lcd2148_data(T+48);
	lcd2148_data(O+48);
}
*/

void lcd2148_showvalue(unsigned char num)	//prints the decimal 3 digit value of num
{
	unsigned char t=0, H=0,T=0,O=0;
	t=num/1000;
	H=(num - (t*1000))/100;
	T=(num - (t*1000) - (H*100))/10;
	//H=num/100;//calculating 100th place no. by dividing by 100
	//T=(num - (H*100))/10;//calculating 10th place no. by substracting 100th place no.& then 2 digit no. divided by 10
	O=(num - (t*1000)- (H*100) - (T*10));//calculating unit place no.by substracting 100th place & 10th place no.
	
	lcd2148_data(t+48);//Sending ASCII values
	lcd2148_data(H+48);
	lcd2148_data(T+48);
	lcd2148_data(O+48);
}

void lcd2148_gotoxy1(unsigned char pos)
{
	lcd2148_cmd(LINE1+pos);
}

void lcd2148_gotoxy2(unsigned char pos)
{
	lcd2148_cmd(LINE2+pos);
}

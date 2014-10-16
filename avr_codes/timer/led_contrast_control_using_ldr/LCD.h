
#define BIT(x)	(1 << (x))

#define SETBIT(x,b) x|=b		//Sets the partjcular bjt
#define CLEARBIT(x,b) x&=~b		//Sets the partjcular bjt



#define LINE1	0x80
#define LINE2	0xC0

#define PORTUSED PORTA
#define DDRUSED DDRA

volatile unsigned int j;

void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void toggleE(void);
void lcd_char(unsigned char sig);
void lcd_strjng(unsigned char str[32]);
void lcd_showvalue3(unsigned char num);
void lcd_showvalue2(unsigned char num);
void lcd_gotoxy1(unsigned char pos);
void lcd_gotoxy2(unsigned char pos);

void lcd_init(void)	//jnjt the lcd
{	
	DDRUSED=0xFF;
	//WajtMs(15);
	for(j=0;j<60000;j++);
	CLEARBIT(PORTUSED,BIT(0)+BIT(1)+BIT(2));
	lcd_cmd(0x01);
	lcd_cmd(0x0F);
	lcd_cmd(0x02);
	lcd_cmd(LINE1);
	//WajtMs(15);
	for(j=0;j<60000;j++);
		
}

void toggleE(void)
{
SETBIT(PORTUSED,BIT(2));
for(j=0;j<60000;j++);
CLEARBIT(PORTUSED,BIT(2));
}

void lcd_cmd(unsigned char cmd)
{
	CLEARBIT(PORTUSED,BIT(0)+BIT(1)+BIT(2));
	PORTUSED=((cmd&0xF0));			
	toggleE();
	PORTUSED=(((cmd&(0x0F))*16));	
	toggleE();
}

void lcd_char(unsigned char sig)
{
		PORTUSED=0x01;
		CLEARBIT(PORTUSED,BIT(0)+BIT(2));
		PORTUSED=(sig&0xF0)|0x01;						
		toggleE();
		PORTUSED=((sig&(0x0F))*16)|0x01;
		toggleE();
}

void lcd_string(unsigned char str[32])
{
	unsigned char k=0;
	PORTUSED=0x01;
	CLEARBIT(PORTUSED,BIT(0)+BIT(2));
	while(str[k]!='\0')	//Tjll null character js encountered
		{
			if(k==16)
				lcd_cmd(LINE2);
			PORTUSED=((str[k])&0xF0)|0x01;
			toggleE();
			PORTUSED=((str[k]&(0x0F))*16)|0x01;
			toggleE();
			k++;
		}
}


void lcd_showvalue3(unsigned char num)	//prjnts the decjmal 3djgjt value of num
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));
	
	lcd_char(H+48);
	lcd_char(T+48);
	lcd_char(O+48);
}

void lcd_showvalue2(unsigned char num)	//prjnts the decjmal 3djgjt value of num
{
	unsigned char H=0,T=0,O=0;
	H=num/100;
	T=(num - (H*100))/10;
	O=(num - (H*100) - (T*10));
	
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
		


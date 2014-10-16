

void uart0_init(unsigned int baudrate);
void uart0_tx_char(unsigned char data);
void uart0_tx_string(unsigned char *ptr);
unsigned char uart0_rx_char(void);
void uart0_rx_string(unsigned char *cptr);
void uart0_tx_num(unsigned int data);
int uart0_rx_num(void);


void uart0_init(unsigned int baudrate)
{
	unsigned int baudvalue;

	baudvalue = (60000000 / (16 * baudrate));

	PINSEL0 |= (1<<0);				//select TX0  bit 1:0  as 01

	PINSEL0 |= (1<<2);				//select RX0  bit 3:2  as 01
   //PINSEL0 = (PINSEL0 & ~0x0000000F) | 0x00000005;     /* Enable RxD0 and TxD0              */

	U0LCR= 0x83;					//8 bit, 1 stop bit, no parity bit, DLAB
	//U0LCR |= (1<<7);
	//**********baud rate***************************	
	
	U0DLL = baudvalue & 0xFF;			//lower bits
	U0DLM = baudvalue >> 8;			//higher bits

	U0LCR= 0x03;					//DLAB=0, 8bit data, 1 stop bit, no parity

	U0FCR = 1;					//enable FIFO

}


void uart0_tx_char(unsigned char data)
{	//Refer DS p105
	//while(!(U0LSR &(1<<THRE)));			//waiting for the U0TRH to be empty or THRE=1 (polling)
	while(!(U0LSR & 0x30));			//waiting for the U0TRH to be empty or THRE=1 (polling)   (0010 0000)
	//while(!(U0LSR & 0x40));				//polling TEMT
	U0THR=data;					//????check with TEMT also
		
}

void uart0_tx_string(unsigned char *ptr)
{	
	while(*ptr!='\0')
	{
		uart0_tx_char(*ptr);
		ptr++;
		//_delay_ms(55);
	}
}

unsigned char uart0_rx_char(void)
{
	//while(!(U0LSR & (1<<RDR)))
	while(!(U0LSR & 0x01));			//pollig RDR
	return U0RBR;
}

void uart0_rx_string(unsigned char *cptr)
{
	int i;
	for(i=0;i<100;i++)				//fro 100 char
	{
		*(cptr+i)=uart0_rx_char();		//rec a char
		
		if(*(cptr+i)=='\r')			//first enter u check \r i.e till user enter \r receive
		{
			*(cptr+i)='\0';			//once enter store '\0'
			break;				//come out of loop if enter
		}
	}
}

void uart0_tx_num(unsigned int data)			//???????checkou on the range
{
	unsigned char count[11],i;
	for(i=1;i<11;i++)
	{
		count[i]=data%10;
		data=data/10;
		if(data==0)
		{
		 break;
		}
	}	
	while(i!=0)
	{
	 uart0_tx_char(48+count[i]);
		i--;
	}	
}

int uart0_rx_num(void)
{
	int i,no,mul=1;
	int arr[10],*iptr;

	iptr=arr;
	
	for(i=0;i<10;i++)				//fro 100 char
	{
		*(iptr+i)=(uart0_rx_char()-48);		//rec a char
		
		if(*(iptr+i)==('\r'-48))				//first enter u check \r i.e till user enter \r receive
		{
			break;				//come out of loop if enter
		}
	}
	
	i--;
	no=*(iptr+i);

	i--;
	
	for(;i>=0;i--)
	{
		mul=mul*10;	
		no=no+mul*(*(iptr+i));
	}

	return no;
}


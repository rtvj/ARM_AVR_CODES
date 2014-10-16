#include"myuart.h"

#define  COLOR_BLACK     0                       /* VT102 Color Codes                                  */
#define  COLOR_RED       1
#define  COLOR_GREEN     2
#define  COLOR_BROWN     3
#define  COLOR_BLUE      4
#define  COLOR_MAGENTA   5
#define  COLOR_CYAN      6
#define  COLOR_WHITE     7

void VT102Attribute (unsigned char fgcolor, unsigned char bgcolor)
{
    UART_Transmit_char(0x1b);
    UART_Transmit_char('[');
    UART_Transmit_num(30 + fgcolor);
    UART_Transmit_char(';');
    UART_Transmit_num(40 + bgcolor);
    UART_Transmit_char('m');
}


void VT102DispStr (unsigned char x, unsigned char y, unsigned char *s, unsigned char fgcolor, unsigned char bgcolor)
{
    VT102Attribute(fgcolor, bgcolor);
    UART_Transmit_char(0x1B);
    UART_Transmit_char('[');
    UART_Transmit_num(y);
    UART_Transmit_char(';');
    UART_Transmit_num(x);
    UART_Transmit_char('H');
    UART_Transmit_string(s);
}
//void VT102DispClrScr (unsigned char fgcolor, unsigned char bgcolor)
void VT102DispClrScr (void)
{
    VT102Attribute(COLOR_RED,COLOR_RED);
    //VT102Attribute(fgcolor,bgcolor);
    UART_Transmit_string("\x1B[2J");
}

void VT102DispChar (unsigned char x, unsigned char y, unsigned char c, unsigned char fgcolor, unsigned char bgcolor)
{
    VT102Attribute(fgcolor, bgcolor);
    UART_Transmit_char(0x1B);
    UART_Transmit_char('[');
    UART_Transmit_num(y);
    UART_Transmit_char(';');
    UART_Transmit_num(x);
    UART_Transmit_char('H');
    UART_Transmit_char(c);
}


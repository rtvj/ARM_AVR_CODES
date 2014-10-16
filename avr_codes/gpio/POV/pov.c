

// 7 LED POV 
#include "POV_letters.h" 
#include <string.h> 
#include <avr/io.h> 
#include <util/delay.h> 

void init(); 
void display(char POVstring[]); 

void init() 
{ 
    DDRC=0xff;//turns portb into output 
} 


void display (char POVstring[])
{ 
   for (int i=(strlen(POVstring)-1); i>=0; i--)    //loops through letters 
   {
      for (int j=(WIDTH-1); j>=0; j--)             //loops between parts
	  { 
	    //writes char for i character and j part
	   
         PORTC = font[(int)POVstring[i]-65][j]; 
         _delay_us(2000);                           //delay between parts 
      } 
      PORTC = 0b11111111; 
      _delay_us(2500);                              //delay between letters 
   } 
} 

int main() 
{ 
   init(); 
   for(;;)
   {                                                     // loop forever 
      _delay_ms(250);                                     //wait to refresh 
      display("vipul");                                        //display string 

   } 
   return 0; 
} 

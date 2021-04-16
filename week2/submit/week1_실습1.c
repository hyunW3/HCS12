#include "main.h"
 // power position : top left
 // LED 0b11111110 : 0 is LED ON, pos : left 
void delay(unsigned int sec);
void main ()
{
  Regs.ddrb.byte = 0b11111111; 
  //Regs.portb.byte = 0b11101010;
	//Insert Application Software Here.
	for (;;){
	   Regs.portb.byte = 0b00111100;
	   delay(5); 
	   Regs.portb.byte = 0b11000011;
	   delay(5);
	   
	}
}

void delay(unsigned int sec){
   unsigned int i;
   while(sec >0){
    for(i=1; i!=0; i++);
    sec--; 
    
   }
  
}
#include "main.h"

//week3 practice 2 - interrupt
void main ()
{  
  // LED ON : 0b0, LED OFF : 0b1
  int_disable();
  ini_interrupt();
  Regs.ddrb.byte = 0b11111111; 	// output init
  Regs.portb.byte =    0b11111101; // LED OFF ,          
  int_enable();
	//Insert Application Software Here.
  for (;;); 

}
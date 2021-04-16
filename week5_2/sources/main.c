#include "main.h"



void main ()
{
//  unsigned int i;
  
  int_disable();
  ini_interrupt();
  Regs.ddrb.byte = 0b11111111; 	// LED output init
  Regs.portb.byte = 0b11110000; // LED ON/OFF way
  
  int_enable();   
  init_atd0(); 
  init_7segment(); 
	
	for (;;);
}


void m_delay(unsigned int m) //µÙ∑π¿Ã ∑Á∆æ
{
 unsigned int i, j; 
    
 //  disable_interrupt(); 
   
 for(i=0;i<m;i++)
    for(j=0;j<2650;j++);  //16MHz : 1msec  

 //   enable_interrupt();
}

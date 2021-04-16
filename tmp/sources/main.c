#include "main.h"
void light7segment(unsigned int cnt)
{
 unsigned char c_cnt = (unsigned char)cnt;
  set_7segment(c_cnt);
}
void m_delay(unsigned int m);
//week3 practice 1 - interrupt
void main ()
{  
  // LED ON : 0b0, LED OFF : 0b1
  unsigned int i;
  int_disable();
  ini_interrupt();
  init_7segment();
  Regs.ddrb.byte = 0b11111111; 	// output init
  Regs.portb.byte =    0b11111111; // LED OFF    
  int_enable();

	//Insert Application Software Here. 
  for (;;){
      i = get_atd0(0);
  	  light7segment(i);
      m_delay(5);
  }

}

void m_delay(unsigned int m) {   
 unsigned int i, j;   
 int_enable();
 for(i=0;i<m;i++)
    for(j=0;j<2650;j++);  //16MHz : 1msec  
 
 int_disable();
}
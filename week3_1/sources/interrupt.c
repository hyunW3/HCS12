#include "interrupt.h"

/*************************************************/
/*  port J as interrupt.   */
/*************************************************/
void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // 인터럽트 포트의 방향 결정
 Pim.piej.byte=0xff;		// 인터럽트 포트의 인터럽트 enable
 Pim.ppsj.byte=0x00;		// 인터럽트 포트의 엣지 설정  
}
void delay(unsigned int sec){
   unsigned int i;
   while(sec >0){
    for(i=1; i!=0; i++);
    sec--; 
    
   }
  
}
void interruptJ_function(void)
{    
  Regs.ddrb.byte = 0b11111111; 	// output init
  // Regs.portb.byte = 0b01111110; // LED ON/OFF way
  // SW2 portJ 0pin, SW3 portJ 1pin
  if(Pim.pifj.byte & (0x01))      // SW2의 인터럽트 발생   
  {    
      Regs.portb.byte = 0b00000000;
      Pim.pifj.byte |= 0x01;    // 인터럽트 플래그 초기화 
    
  } 
  else if(Pim.pifj.byte & (0x02	))  // SW3의 인터럽트 발생  portJ 1pin 
  {  
      Regs.portb.byte = 0b11111111;
      Pim.pifj.byte |= 0x02;   // 인터럽트 플래그 초기화 
  }
    
}

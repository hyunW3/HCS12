#include "interrupt.h"
#include <string.h>
#include <stdio.h>
/*************************************************/
/*  port J as interrupt.   */
/*************************************************/ 
extern int interrupt_sw1;
extern int interrupt_sw2;
extern int interrupt_sw3;
   
void m_delay(unsigned int m);

void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // 인터럽트 포트의 방향 결정
 Pim.piej.byte=0xff;		// 인터럽트 포트의 인터럽트 enable
 Pim.ppsj.byte=0x00;		// 인터럽트 포트의 엣지 설정  
}
void interruptJ_function(void)
{ 
  int i=0;
    
  // SW2 portJ 0pin, SW3 portJ 1pin
  if(Pim.pifj.byte & (0x01))      // SW2의 인터럽트 발생   
  {    
      interrupt_sw2=1;
 
     Pim.pifj.byte |= 0x01;    // 인터럽트 플래그 초기화 
    
  } 
  else if(Pim.pifj.byte & (0x02	))  // SW3의 인터럽트 발생  portJ 1pin 
  {       
      interrupt_sw3=1;
      Pim.pifj.byte |= 0x02;   // 인터럽트 플래그 초기화 
  }
    
}

void interruptX_function (void)    //XIRQ interrupt 서비스 함수  
{	 
   interrupt_sw1 = 1;   
}
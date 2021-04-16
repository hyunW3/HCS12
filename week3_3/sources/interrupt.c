#include "interrupt.h"

/*
  포트 J를 인터럽트로 사용하도록 설정한다.  
*/
void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // 인터럽트 포트의 방향 결정
 Pim.piej.byte=0xff;		// 인터럽트 포트의 인터럽트 enable
 Pim.ppsj.byte=0x00;		// 인터럽트 포트의 엣지 설정  
}

/*
  sw2,3 set portJ operation.	
  sw2 rotate clockwise                 	 
  sw3 rotate counter clockwise
  sw1 is stop			               
*/

void interruptJ_function(void)
{   
// SW2 portJ 0pin, SW3 portJ 1pin
  if(Pim.pifj.byte & (0x01))      // SW2의 인터럽트 발생 
  {    
      init_rti(1);
      Pim.pifj.byte |= 0x01;    // 인터럽트 플래그 초기화 
    
  } 
  else if(Pim.pifj.byte & (0x02))  // SW3의 인터럽트 발생   
  {  
      init_rti(2);
      Pim.pifj.byte |= 0x02;   // 인터럽트 플래그 초기화 
  }
    
}
void interruptX_function (void)    //XIRQ interrupt 서비스 함수  
{	    
    init_rti(3);     
}
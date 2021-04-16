#include "interrupt.h"

/*************************************************/
/*  port J as interrupt.   */
/*************************************************/
void m_delay(unsigned int m);
void light7segment(unsigned int cnt);

void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // 인터럽트 포트의 방향 결정
 Pim.piej.byte=0xff;		// 인터럽트 포트의 인터럽트 enable
 Pim.ppsj.byte=0x00;		// 인터럽트 포트의 엣지 설정  
}
void interruptJ_function(void)
{ 
  unsigned int i;
  Regs.ddrb.byte = 0b11111111; 	// output init   
  // SW2 portJ 0pin, SW3 portJ 1pin
  if(Pim.pifj.byte & (0x01))      // SW2의 인터럽트 발생   
  {    
      
    Regs.portb.byte = 0b01110011; // LED ON/OFF way
     Pim.ddrh.byte= 0xFF;				//7-세그먼트 사용 하는 포트 출력 방향으로 결정
    	i=get_atd0(0);		//ATD 값을 받아옴
    	light7segment(i);	// ATD 값 Segment출력
    
	    m_delay(50);
     Pim.pifj.byte |= 0x01;    // 인터럽트 플래그 초기화 
    
  } 
  else if(Pim.pifj.byte & (0x02	))  // SW3의 인터럽트 발생  portJ 1pin 
  {       
      Pim.ddrh.byte= 0x00;				// 7 Segment OFF
      Regs.portb.byte = 0b11111111;
      Pim.pifj.byte |= 0x02;   // 인터럽트 플래그 초기화 
  }
    
}

void m_delay(unsigned int m) 
{
 unsigned int i, j; 
     
   
 for(i=0;i<m;i++)
    for(j=0;j<2650;j++);  //16MHz : 1msec  

}
void light7segment(unsigned int cnt)
{
 //	ATD 값을 0~9로 변환하는 프로그램을 작성하시오.
 unsigned char c_cnt = (unsigned char)cnt;
  set_7segment(c_cnt);
}
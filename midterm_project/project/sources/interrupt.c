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
 
 Pim.ddrj.byte=0b00000000;    // ���ͷ�Ʈ ��Ʈ�� ���� ����
 Pim.piej.byte=0xff;		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
 Pim.ppsj.byte=0x00;		// ���ͷ�Ʈ ��Ʈ�� ���� ����  
}
void interruptJ_function(void)
{ 
  int i=0;
    
  // SW2 portJ 0pin, SW3 portJ 1pin
  if(Pim.pifj.byte & (0x01))      // SW2�� ���ͷ�Ʈ �߻�   
  {    
      interrupt_sw2=1;
 
     Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    
  } 
  else if(Pim.pifj.byte & (0x02	))  // SW3�� ���ͷ�Ʈ �߻�  portJ 1pin 
  {       
      interrupt_sw3=1;
      Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
  }
    
}

void interruptX_function (void)    //XIRQ interrupt ���� �Լ�  
{	 
   interrupt_sw1 = 1;   
}
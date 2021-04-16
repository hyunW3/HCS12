#include "interrupt.h"

/*
  ��Ʈ J�� ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�.  
*/
void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // ���ͷ�Ʈ ��Ʈ�� ���� ����
 Pim.piej.byte=0xff;		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
 Pim.ppsj.byte=0x00;		// ���ͷ�Ʈ ��Ʈ�� ���� ����  
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
  if(Pim.pifj.byte & (0x01))      // SW2�� ���ͷ�Ʈ �߻� 
  {    
      init_rti(1);
      Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    
  } 
  else if(Pim.pifj.byte & (0x02))  // SW3�� ���ͷ�Ʈ �߻�   
  {  
      init_rti(2);
      Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
  }
    
}
void interruptX_function (void)    //XIRQ interrupt ���� �Լ�  
{	    
    init_rti(3);     
}
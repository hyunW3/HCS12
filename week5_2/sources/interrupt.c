#include "interrupt.h"

/*************************************************/
/*  port J as interrupt.   */
/*************************************************/
void m_delay(unsigned int m);
void light7segment(unsigned int cnt);

void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // ���ͷ�Ʈ ��Ʈ�� ���� ����
 Pim.piej.byte=0xff;		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
 Pim.ppsj.byte=0x00;		// ���ͷ�Ʈ ��Ʈ�� ���� ����  
}
void interruptJ_function(void)
{ 
  unsigned int i;
  Regs.ddrb.byte = 0b11111111; 	// output init   
  // SW2 portJ 0pin, SW3 portJ 1pin
  if(Pim.pifj.byte & (0x01))      // SW2�� ���ͷ�Ʈ �߻�   
  {    
      
    Regs.portb.byte = 0b01110011; // LED ON/OFF way
     Pim.ddrh.byte= 0xFF;				//7-���׸�Ʈ ��� �ϴ� ��Ʈ ��� �������� ����
    	i=get_atd0(0);		//ATD ���� �޾ƿ�
    	light7segment(i);	// ATD �� Segment���
    
	    m_delay(50);
     Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    
  } 
  else if(Pim.pifj.byte & (0x02	))  // SW3�� ���ͷ�Ʈ �߻�  portJ 1pin 
  {       
      Pim.ddrh.byte= 0x00;				// 7 Segment OFF
      Regs.portb.byte = 0b11111111;
      Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
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
 //	ATD ���� 0~9�� ��ȯ�ϴ� ���α׷��� �ۼ��Ͻÿ�.
 unsigned char c_cnt = (unsigned char)cnt;
  set_7segment(c_cnt);
}
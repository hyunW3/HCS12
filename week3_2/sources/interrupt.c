#include "interrupt.h"

/*************************************************/
/*  port J as interrupt.   */
/*************************************************/
void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // ���ͷ�Ʈ ��Ʈ�� ���� ����
 Pim.piej.byte=0xff;		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
 Pim.ppsj.byte=0x00;		// ���ͷ�Ʈ ��Ʈ�� ���� ����  
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
  //Regs.ddrb.byte = 0b11111111; 	// output init
  // Regs.portb.byte = 0b01111110; // LED ON/OFF way
  // SW2 portJ 0pin, SW3 portJ 1pin
  if(Pim.pifj.byte & (0x01))      // SW2�� ���ͷ�Ʈ �߻�   
  {    
      if (Regs.portb.byte == 0x7F){     // The most right
          // do nothing
      }else { 
         Regs.portb.byte = Regs.portb.byte <<1;
         Regs.portb.byte = Regs.portb.byte + 0b1; 
      }
      Pim.pifj.byte |= 0x01;    // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
    
  } 
  else if(Pim.pifj.byte & (0x02	))  // SW3�� ���ͷ�Ʈ �߻�  portJ 1pin 
  {  
      //Regs.portb.byte = 0b11111111;     // LED OFF
      if (Regs.portb.byte == 0xFE){  // The most left
        // 0x1111 1110 case, do nothing
        
      } else {
        Regs.portb.byte = Regs.portb.byte >>1;
        Regs.portb.byte = Regs.portb.byte + 0x80;
      }
      Pim.pifj.byte |= 0x02;   // ���ͷ�Ʈ �÷��� �ʱ�ȭ 
  }
    
}
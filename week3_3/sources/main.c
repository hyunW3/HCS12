#include "main.h"

void main ()
{  
  int_disable();                      //���ͷ�Ʈ disable
  																		//����Ÿ�� ���ͷ�Ʈ �ʱ�ȭ 
  init_rti(3);				
  ini_interrupt();			//���ͷ�Ʈ �ʱ�ȭ      (�� 0.5ms���� ���ͷ�Ʈ)
  																	
  int_enable();				//���ͷ�Ʈ enanle
  xint_enable();			
  
  Pim.ddrh.byte=0b11111111; 
  Pim.pth.byte = 0x01; // 7 segment start LED      0b0000 0001
    
	//Insert Application Software Here.
	for (;;); 

}
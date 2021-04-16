#include "main.h"

void light7segment(unsigned int cnt)
{
 //	ATD ���� 0~9�� ��ȯ�ϴ� ���α׷��� �ۼ��Ͻÿ�.
 unsigned char c_cnt = (unsigned char)cnt;
  set_7segment(c_cnt);
}

void main ()
{
  unsigned int i;
  
  
  init_atd0();
  init_7segment();
  
	Page.ddrk.byte = (0x01	);	          // �߱��� ����� ����	

	//Insert Application Software Here
	for (;;){     
  	i=get_atd0(0);		//ATD ���� �޾ƿ�
  	 
  	light7segment(i);	// ATD �� Segment���
    
	  m_delay(50);
	}
		
	for (;;);
}


void m_delay(unsigned int m) //������ ��ƾ
{
 unsigned int i, j; 
    
 //  disable_interrupt(); 
 //int_disable();
   
 for(i=0;i<m;i++)
    for(j=0;j<2650;j++);  //16MHz : 1msec  

 //   enable_interrupt();
 //int_enable();
}

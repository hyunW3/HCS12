#include "main.h"

void light7segment(unsigned int cnt)
{
 //	ATD 값을 0~9로 변환하는 프로그램을 작성하시오.
 unsigned char c_cnt = (unsigned char)cnt;
  set_7segment(c_cnt);
}

void main ()
{
  unsigned int i;
  
  
  init_atd0();
  init_7segment();
  
	Page.ddrk.byte = (0x01	);	          // 발광부 입출력 설정	

	//Insert Application Software Here
	for (;;){     
  	i=get_atd0(0);		//ATD 값을 받아옴
  	 
  	light7segment(i);	// ATD 값 Segment출력
    
	  m_delay(50);
	}
		
	for (;;);
}


void m_delay(unsigned int m) //딜레이 루틴
{
 unsigned int i, j; 
    
 //  disable_interrupt(); 
 //int_disable();
   
 for(i=0;i<m;i++)
    for(j=0;j<2650;j++);  //16MHz : 1msec  

 //   enable_interrupt();
 //int_enable();
}

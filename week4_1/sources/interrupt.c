#include "interrupt.h"
#include <stdio.h>


/*
  포트 J를 인터럽트로 사용하도록 설정한다.
*/
void ini_interrupt(void){
 
 Pim.ptj.byte=(0x00 );    // 인터럽트 포트의 방향 결정
 Pim.piej.byte=(0xFF);		// 인터럽트 포트의 인터럽트 enable
 Pim.ppsj.byte=(0x00);		// 인터럽트 포트의 엣지 설정
 
}

/*
  스위치 2,3에 연결된 포트 J의 동작을 설정한다.
  스위치 2를 누르면 cnt 숫자가 증가하고 LCD에 표시한다.
  스위치 3을 누르면 cnt 숫자가 감소하고 LCD에 표시한다. 
  스위치 1을 누르면 cnt값을 세크먼트 표시한다. 
*/

int cnt = 0;      //Count 값
char str1[16]=""; //문자열 저장

void interruptJ_function (void){


  if(Pim.pifj.byte & (0x01))  {   // SW2의 인터럽트 발생
 
    cnt++;
    if( cnt > 9) //cnt값은 0~9
      cnt=(9);
    
    (void) sprintf((str1), "Count = %d", (cnt));  //문자열 저장
    write_string((0x00), (str1));    // write_string(offset,char *str)
    
    Pim.pifj.byte |= (0x01);    // 인터럽트 플래그 초기화 (하지않으면 루틴을 빠져나가지 못함)
    
  } 
  else if(Pim.pifj.byte & (0x02))  {  // SW3의 인터럽트 발생
 
    cnt--;
    if( cnt <0) //cnt값은 0~9
      cnt=(0);                                                            
    (void) sprintf((str1), "Count = %d", (cnt));  //문자열 저장
    write_string((0x00), (str1));
        
 
    Pim.pifj.byte |= (0x02);   // 인터럽트 플래그 초기화 (하지않으면 루틴을 빠져나가지 못함)
  }
  
}



void interruptX_function(void){
    switch(cnt){
      case 0:
        Pim.pth.byte = val0;   
        break;
      case 1:   
        Pim.pth.byte = val1;   
        break;  
      case 2:     
        Pim.pth.byte = val2;   
        break;
      case 3:        
        Pim.pth.byte = val3;   
        break;
      case 4:    
        Pim.pth.byte = val4;   
        break;
      case 5:       
        Pim.pth.byte = val5;   
        break;
      case 6:        
        Pim.pth.byte = val6;   
        break;  
      case 7:  
        Pim.pth.byte = val7;   
        break;
      case 8:  
        Pim.pth.byte = val8;   
        break;
      case 9:  
        Pim.pth.byte = val9;   
        break;
      default:           
        Pim.pth.byte = 0x00;   
        break;
    }
       //세그먼트에 cnt값 출력

}
  
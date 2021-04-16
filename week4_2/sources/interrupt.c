#include "interrupt.h"
#include <stdio.h>


/*
 port J as interrupt
*/
void ini_interrupt(void){
 
 Pim.ptj.byte=(0x00);    // 인터럽트 포트의 방향 결정
 Pim.piej.byte=(0xFF);		// 인터럽트 포트의 인터럽트 enable
 Pim.ppsj.byte=(0x00);		// 인터럽트 포트의 엣지 설정
 
}

/*
  week4 - practice 2
   SW2 -> NUM1++
   SW3 -> NUM2++
   SW1 -> NUM1*NUM2

  */

int num1 = 0;      //cum 
int num2 = 0;      //cum
int product = 0;      //cum
char str[16]=""; //문자열 저장

void interruptJ_function (void){


  if(Pim.pifj.byte & (0x01))  {   // SW2의 인터럽트 발생
 
    num1++;
    
    (void) sprintf((str), "Num1=%d", (num1));  //문자열 저장
    write_string((0x00), (str));
    
    Pim.pifj.byte |= (0x01);    // 인터럽트 플래그 초기화 (하지않으면 루틴을 빠져나가지 못함)
    
  } 
  else if(Pim.pifj.byte & (0x02))  {  // SW3의 인터럽트 발생
      
    num2++;
    
    (void) sprintf((str), "Num2=%d", (num2));  //문자열 저장
    write_string((0x08), (str));
        
 
    Pim.pifj.byte |= (0x02);   // 인터럽트 플래그 초기화 (하지않으면 루틴을 빠져나가지 못함)
  }
  
}



void interruptX_function(void){

    (void) sprintf((str), "Result= %d", (num1*num2));  //문자열 저장
    write_string((0x40), (str));
       //세그먼트에 cnt값 출력

}
  
#include "7segment.h"

/*  
7-세그먼트에 사용되는 포트를 초기화한다.
*/
void init_7segment(void) 
{
  Pim.ddrh.byte = 0xFF;       //7segment as output port
  Pim.pth.byte = 0x00;      // 7 segment OFF
}

/*
  0~9 중에 하나의 수를 입력하면 그 값을 7-세그먼트에 출력한다.
  */
void set_7segment(unsigned char number) 
{
  switch (number) 
  {
    case 0 : 
      Pim.pth.byte=(val0);		//7-세그먼트 에서 '0'이 출력되도록 포트 값을 설정
      break;  
    case 1 : 
      Pim.pth.byte=(val1);		//7-세그먼트 에서 '1'이 출력되도록 포트 값을 설정
      break;
    case 2 : 
      Pim.pth.byte=(val2);		//7-세그먼트 에서 '2'가 출력되도록 포트 값을 설정
      break;
    case 3 : 
      Pim.pth.byte=(val3);		//7-세그먼트 에서 '3'이 출력되도록 포트 값을 설정
      break;
    case 4 : 
      Pim.pth.byte=(val4);		//7-세그먼트 에서 '4'가 출력되도록 포트 값을 설정
      break;
    case 5 : 
      Pim.pth.byte=(val5);		//7-세그먼트 에서 '5'가 출력되도록 포트 값을 설정
      break;
    case 6 : 
      Pim.pth.byte=(val6);		//7-세그먼트 에서 '6'이 출력되도록 포트 값을 설정
      break;
    case 7 : 
      Pim.pth.byte=(val7);		//7-세그먼트 에서 '7'이 출력되도록 포트 값을 설정
      break;
    case 8 : 
      Pim.pth.byte=(val8);		//7-세그먼트 에서 '8'이 출력되도록 포트 값을 설정
      break;                                        
    case 9 : 
      Pim.pth.byte=(val9);		//7-세그먼트 에서 '9'가 출력되도록 포트 값을 설정
      break;
    case 10 :
      Pim.pth.byte=(0x00);		//7-세그먼트 에서 소등되는 값을 설정
      break;  
    default:
      break;
  }
  return; 
}

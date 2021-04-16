#include "rti.h"

int scaler;
int i = 0;
int pin = 0x01;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s

/*************************************************/
/*  리얼타임 인터럽트를 초기화 한다.*/
/*************************************************/
void init_rti(int s)
{
	scaler = s;
	Crg.rtictl.byte = (0b00011000);     //리얼타임 인터럽트의 속도 결정(0.5ms 로 하시오)
	Crg.crgint.byte |= 0b10000000;		//리얼타임 인터럽트 enable
	
}

/*************************************************/
/*  리얼타임 인터럽트가 발생할 때마다 */
/*  7-세그먼트가 동작. */
/*  ex) Pim.pth.byte = 0x01       세그먼트 값출력*/
/*  자유롭게 코딩을 하시오.			*/
/*************************************************/
void rti_service(void) 
{
  if(scaler==(1))    //   sw2 interrupt case
  {         
     // Pim.pth.byte = 0x02;       //0b0000 0010 
          switch(Pim.pth.byte){
            case 0x01:
              Pim.pth.byte = 0x02;
              break;
            case 0x02:
              Pim.pth.byte = 0x04;
              break;
            case 0x04:
              Pim.pth.byte = 0x08;
              break;
            case 0x08:   
              Pim.pth.byte = 0x10;
              break;
            case 0x10:  
              Pim.pth.byte = 0x20;
              break;
            case 0x20:    
              Pim.pth.byte = 0x01;
              break;
             default : // error case    
              Pim.pth.byte = 0x80;        //dot emit
              break;
          }
  } 
  
  else if(scaler==(2))  //   sw3 interrupt case 
  {     
     //  Pim.pth.byte = 0x80;       // 0b1000 0000
          switch(Pim.pth.byte){
            case 0x01:
              Pim.pth.byte = 0x20;
              break;
            case 0x02:
              Pim.pth.byte = 0x01;
              break;
            case 0x04:
              Pim.pth.byte = 0x02;
              break;
            case 0x08:   
              Pim.pth.byte = 0x04;
              break;
            case 0x10:  
              Pim.pth.byte = 0x08;
              break;
            case 0x20:    
              Pim.pth.byte = 0x10;
              break;
             default : // error case    
              Pim.pth.byte = 0x80;        //dot emit
              break;
          }  
  }
  
  else if(scaler==(3))    //   XIRQ interrupt case
  {
       Pim.pth.byte = Pim.pth.byte ;
  }else { //exception case
        Pim.pth.byte = 0x80;
  }
}

/*************************************************/
/*  리얼타임 인터럽트가 발생할 때의 동작을 정의한다. */
/*************************************************/

/* 0.5초 마다 rti_handler 실행 */
void rti_handler(void)
{
	static int count = 0;
	
	count++;

	if (count >= (2000)) {
	 /*약 1초마다 실행*/
		// process task
		rti_service();
  	count = 0;

		
	}
	// clear flag
    Crg.crgflg.bit.rtif = 1;    // 실시간 인터럽트 플래그 초기화

}

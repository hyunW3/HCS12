#include "atd.h"
/*****************************************************/
/*  ATD 모듈을 초기화 한다.								           */
/*****************************************************/
int val;
void init_atd0(void) {

  //Atd0.atdctl2.byte = (0x82);       //Power Up    -> interrupt flag problem (portj interrupt not working with 0x82)
  Atd0.atdctl2.byte = (0x80);       //Power Up
  Atd0.atdctl3.byte = (0x10);				//Conversion Sequence Length = 2, FIFO off, Backgroud Debug freeze: Continue conversion
  Atd0.atdctl4.byte = (0x6D);				//A/D resolution 10bit, Sample time 16 A/D conversion clock period
  																  //Clock prescale value: (divided by 28)
  Atd0.atdctl5.byte = (0xA0);				//Right justification, Unsigned, Continuous Scan, Multi-Channel off, AN0 
}

/******************************************************/
/*  입력 받은 채널에 해당하는 ATD 변환 값을 반환한다.	*/
/******************************************************/
int get_atd0(int channel) 
{ 
  //Write to ATDCTL5 (a new conversion sequence is started) 
  Atd0.atdctl5.byte |= (0x00);	    
 
  if (channel >= 0 && channel <= 7) {     // Check channel range
    //range 419~643
     val  = (int)(Atd0.atddr[channel].d10);
     if(val>=640) return 9;
     else if(val<422) return 0;
     else return (int)((val-390)/30);    // return ATD result register data
  }
  else
    return -1;                                  // Invalid channel
}




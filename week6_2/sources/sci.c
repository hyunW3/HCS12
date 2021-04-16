                                                             
#include "main.h"
unsigned char *txbuffer_sci0; //text를 저장하는 버퍼이다. 
int txoffset_sci0;            //text문자열 길이를 알기위해 필요한 변수이다.
unsigned char *rxbuffer_sci0; //rx를 저장하는 버퍼이다.


/*********************************************************/
/*  시리얼 통신 0번 채널을 초기화 한다.				                       */
/*********************************************************/ 
void init_sci0(int baud_rate, unsigned char *rxbuf) 
{
/*sci를 초기화 하는 함수이다. bps와 문자열의 길이 그리고 송수신 interrupt를 사용할지 등을 결정한다.*/
  unsigned long oscclk, modclk;  //SCIBD register의 SBR을 설정하기 위한 변수
  unsigned short br;    //우리 얻고자 하는 bps를 저장하는 변수
  oscclk = 16000000;	  //MCU의 주파수는 16 MHz이다.
  modclk = oscclk/2 ;	  //Set SCI module clock = (Oscillator Freq.)/2
  br = modclk / 16 / baud_rate ;    
  //Set BR, SCI baud rate = (SCI module clock)/(16*BR)
/*위의 식들은 우리가 사용하는 MCU의 설정에 의해 정해지는 식이다. */

  Sci0.scibd.word =  br;  //설정한 BR 값을 SCIBD register에 저장
  Sci0.scicr1.byte =0x00;  //SCI 설정 관련 register 초기화. Normal operation & 8 data bit format & Parity disabled
  Sci0.scicr2.byte = 0x24;//0x2C ;  //SCI 설정 관련 register 초기화. transmit & receive & receive interrupt 활성화 
/* 여기서 transmit interrpt는 보낼 때 interrupt를 발생시키기 때문에 초기화 해 줄 필요없다. */ 
	txoffset_sci0 = 0;          
	rxbuffer_sci0 = rxbuf;
/*각각의 offset과 buffer를 초기화 한다.*/     
}
 
void write_sci0(unsigned char *text)
{
/*이 함수는 입력받은 문자열을 컴퓨터에 보내는 역할을 하는 함수이다. transmit interrupt를 발생시켜 sci interrupt handler함수를 호출하게 된다*/

	txbuffer_sci0 = text; 
/*문자열 길이를 offset에 저장 시킨다.*/
  Sci0.scicr2.byte |= (0x88);         //TIE & TE 활성화   
}

void sci0_handler(void)
{
  //port 0 : ON / 1 : OFF
  Regs.portb.byte = (0xFF);   // 포트 B의 모든 핀을 1로 설정
  Pim.ptm.byte = (0xC0);      // 포트 M의 6,7번 핀을 1로 설정
  
  if (Sci0.scisr1.bit.tdre == 1)  
/*수신 상태가 아닌 송신 상태이면 TDRE가 1이되고 위와 같이 status와 비교해 주면 된다. */
  {
    Sci0.scidrl.byte = *txbuffer_sci0;    // scidrl에 송신할 데이터 저장
    txbuffer_sci0++;   
    
    if(*txbuffer_sci0 == '\0')
    { 
      Sci0.scicr2.byte &= (0x7F);           // Transmitter Interrupt Enable Bit만 클리어
    }
    
  }
}


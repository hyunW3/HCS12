                                                             
#include "main.h"
unsigned char *txbuffer_sci0; //text�� �����ϴ� �����̴�. 
int txoffset_sci0;            //text���ڿ� ���̸� �˱����� �ʿ��� �����̴�.
unsigned char *rxbuffer_sci0; //rx�� �����ϴ� �����̴�.


/*********************************************************/
/*  �ø��� ��� 0�� ä���� �ʱ�ȭ �Ѵ�.				                       */
/*********************************************************/ 
void init_sci0(int baud_rate, unsigned char *rxbuf) 
{
/*sci�� �ʱ�ȭ �ϴ� �Լ��̴�. bps�� ���ڿ��� ���� �׸��� �ۼ��� interrupt�� ������� ���� �����Ѵ�.*/
  unsigned long oscclk, modclk;  //SCIBD register�� SBR�� �����ϱ� ���� ����
  unsigned short br;    //�츮 ����� �ϴ� bps�� �����ϴ� ����
  oscclk = 16000000;	  //MCU�� ���ļ��� 16 MHz�̴�.
  modclk = oscclk/2 ;	  //Set SCI module clock = (Oscillator Freq.)/2
  br = modclk / 16 / baud_rate ;    
  //Set BR, SCI baud rate = (SCI module clock)/(16*BR)
/*���� �ĵ��� �츮�� ����ϴ� MCU�� ������ ���� �������� ���̴�. */

  Sci0.scibd.word =  br;  //������ BR ���� SCIBD register�� ����
  Sci0.scicr1.byte =0x00;  //SCI ���� ���� register �ʱ�ȭ. Normal operation & 8 data bit format & Parity disabled
  Sci0.scicr2.byte = 0x24;//0x2C ;  //SCI ���� ���� register �ʱ�ȭ. transmit & receive & receive interrupt Ȱ��ȭ 
/* ���⼭ transmit interrpt�� ���� �� interrupt�� �߻���Ű�� ������ �ʱ�ȭ �� �� �ʿ����. */ 
	txoffset_sci0 = 0;          
	rxbuffer_sci0 = rxbuf;
/*������ offset�� buffer�� �ʱ�ȭ �Ѵ�.*/     
}
 
void write_sci0(unsigned char *text)
{
/*�� �Լ��� �Է¹��� ���ڿ��� ��ǻ�Ϳ� ������ ������ �ϴ� �Լ��̴�. transmit interrupt�� �߻����� sci interrupt handler�Լ��� ȣ���ϰ� �ȴ�*/

	txbuffer_sci0 = text; 
/*���ڿ� ���̸� offset�� ���� ��Ų��.*/
  Sci0.scicr2.byte |= (0x88);         //TIE & TE Ȱ��ȭ   
}

void sci0_handler(void)
{
  //port 0 : ON / 1 : OFF
  Regs.portb.byte = (0xFF);   // ��Ʈ B�� ��� ���� 1�� ����
  Pim.ptm.byte = (0xC0);      // ��Ʈ M�� 6,7�� ���� 1�� ����
  
  if (Sci0.scisr1.bit.tdre == 1)  
/*���� ���°� �ƴ� �۽� �����̸� TDRE�� 1�̵ǰ� ���� ���� status�� ���� �ָ� �ȴ�. */
  {
    Sci0.scidrl.byte = *txbuffer_sci0;    // scidrl�� �۽��� ������ ����
    txbuffer_sci0++;   
    
    if(*txbuffer_sci0 == '\0')
    { 
      Sci0.scicr2.byte &= (0x7F);           // Transmitter Interrupt Enable Bit�� Ŭ����
    }
    
  }
}


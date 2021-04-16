                                                             
#include "main.h"
unsigned char *txbuffer_sci0; //text�� �����ϴ� �����̴�. 
int txoffset_sci0;            //text���ڿ� ���̸� �˱����� �ʿ��� �����̴�.         
unsigned char *rxbuffer_sci0; //rx�� �����ϴ� �����̴�.
extern unsigned char RX[40];
extern int ready;
extern int timeout;  
int offset=0;

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
  offset =0; 
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
    
  //if(Sci0.scisr1.bit.rdrf == 1 && ready == 0){   //���� �����̸� RDRF�� �ݵ�� 1�� �Ǿ��ִ�.
  if(Sci0.scisr1.bit.rdrf == 1){   //���� �����̸� RDRF�� �ݵ�� 1�� �Ǿ��ִ�.
     
     *rxbuffer_sci0 = Sci0.scidrl.byte;
     if(*rxbuffer_sci0 == '<') offset =0;                         
     RX[offset++] =  *rxbuffer_sci0;
     //write_sci0(rxbuffer_sci0);
     //write_char(LCD_LINE2+offset,*rxbuffer_sci0);
     if(*rxbuffer_sci0 == '>' || offset >=27) {
      RX[0] = '<';     // unexpected
      RX[offset]='\0';
       ready=1;
       offset=0;
     }
     
  } else if (Sci0.scisr1.bit.tdre == 1)  
/*���� ���°� �ƴ� �۽� �����̸� TDRE�� 1�̵ǰ� ���� ���� status�� ���� �ָ� �ȴ�. */
  {
    Sci0.scidrl.byte = *txbuffer_sci0;    // scidrl�� �۽��� ������ ����
    txbuffer_sci0++;   
    //rxbuffer_sci0 = (unsigned char*)">01110111<"; //tmp
    if(*txbuffer_sci0 == '\0')
    { 
      Sci0.scicr2.byte &= (0x7F);           // Transmitter Interrupt Enable Bit�� Ŭ����
    }
    
  }
}


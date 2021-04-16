#include "rti.h"

int scaler;
int i = 0;
int pin = 0x01;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s

/*************************************************/
/*  ����Ÿ�� ���ͷ�Ʈ�� �ʱ�ȭ �Ѵ�.*/
/*************************************************/
void init_rti(int s)
{
	scaler = s;
	Crg.rtictl.byte = (0b00011000);     //����Ÿ�� ���ͷ�Ʈ�� �ӵ� ����(0.5ms �� �Ͻÿ�)
	Crg.crgint.byte |= 0b10000000;		//����Ÿ�� ���ͷ�Ʈ enable
	
}

/*************************************************/
/*  ����Ÿ�� ���ͷ�Ʈ�� �߻��� ������ */
/*  7-���׸�Ʈ�� ����. */
/*  ex) Pim.pth.byte = 0x01       ���׸�Ʈ �����*/
/*  �����Ӱ� �ڵ��� �Ͻÿ�.			*/
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
/*  ����Ÿ�� ���ͷ�Ʈ�� �߻��� ���� ������ �����Ѵ�. */
/*************************************************/

/* 0.5�� ���� rti_handler ���� */
void rti_handler(void)
{
	static int count = 0;
	
	count++;

	if (count >= (2000)) {
	 /*�� 1�ʸ��� ����*/
		// process task
		rti_service();
  	count = 0;

		
	}
	// clear flag
    Crg.crgflg.bit.rtif = 1;    // �ǽð� ���ͷ�Ʈ �÷��� �ʱ�ȭ

}

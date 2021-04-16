#include "interrupt.h"
#include <stdio.h>


/*
 port J as interrupt
*/
void ini_interrupt(void){
 
 Pim.ptj.byte=(0x00);    // ���ͷ�Ʈ ��Ʈ�� ���� ����
 Pim.piej.byte=(0xFF);		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
 Pim.ppsj.byte=(0x00);		// ���ͷ�Ʈ ��Ʈ�� ���� ����
 
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
char str[16]=""; //���ڿ� ����

void interruptJ_function (void){


  if(Pim.pifj.byte & (0x01))  {   // SW2�� ���ͷ�Ʈ �߻�
 
    num1++;
    
    (void) sprintf((str), "Num1=%d", (num1));  //���ڿ� ����
    write_string((0x00), (str));
    
    Pim.pifj.byte |= (0x01);    // ���ͷ�Ʈ �÷��� �ʱ�ȭ (���������� ��ƾ�� ���������� ����)
    
  } 
  else if(Pim.pifj.byte & (0x02))  {  // SW3�� ���ͷ�Ʈ �߻�
      
    num2++;
    
    (void) sprintf((str), "Num2=%d", (num2));  //���ڿ� ����
    write_string((0x08), (str));
        
 
    Pim.pifj.byte |= (0x02);   // ���ͷ�Ʈ �÷��� �ʱ�ȭ (���������� ��ƾ�� ���������� ����)
  }
  
}



void interruptX_function(void){

    (void) sprintf((str), "Result= %d", (num1*num2));  //���ڿ� ����
    write_string((0x40), (str));
       //���׸�Ʈ�� cnt�� ���

}
  
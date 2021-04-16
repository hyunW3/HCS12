#include "interrupt.h"
#include <stdio.h>


/*
  ��Ʈ J�� ���ͷ�Ʈ�� ����ϵ��� �����Ѵ�.
*/
void ini_interrupt(void){
 
 Pim.ptj.byte=(0x00 );    // ���ͷ�Ʈ ��Ʈ�� ���� ����
 Pim.piej.byte=(0xFF);		// ���ͷ�Ʈ ��Ʈ�� ���ͷ�Ʈ enable
 Pim.ppsj.byte=(0x00);		// ���ͷ�Ʈ ��Ʈ�� ���� ����
 
}

/*
  ����ġ 2,3�� ����� ��Ʈ J�� ������ �����Ѵ�.
  ����ġ 2�� ������ cnt ���ڰ� �����ϰ� LCD�� ǥ���Ѵ�.
  ����ġ 3�� ������ cnt ���ڰ� �����ϰ� LCD�� ǥ���Ѵ�. 
  ����ġ 1�� ������ cnt���� ��ũ��Ʈ ǥ���Ѵ�. 
*/

int cnt = 0;      //Count ��
char str1[16]=""; //���ڿ� ����

void interruptJ_function (void){


  if(Pim.pifj.byte & (0x01))  {   // SW2�� ���ͷ�Ʈ �߻�
 
    cnt++;
    if( cnt > 9) //cnt���� 0~9
      cnt=(9);
    
    (void) sprintf((str1), "Count = %d", (cnt));  //���ڿ� ����
    write_string((0x00), (str1));    // write_string(offset,char *str)
    
    Pim.pifj.byte |= (0x01);    // ���ͷ�Ʈ �÷��� �ʱ�ȭ (���������� ��ƾ�� ���������� ����)
    
  } 
  else if(Pim.pifj.byte & (0x02))  {  // SW3�� ���ͷ�Ʈ �߻�
 
    cnt--;
    if( cnt <0) //cnt���� 0~9
      cnt=(0);                                                            
    (void) sprintf((str1), "Count = %d", (cnt));  //���ڿ� ����
    write_string((0x00), (str1));
        
 
    Pim.pifj.byte |= (0x02);   // ���ͷ�Ʈ �÷��� �ʱ�ȭ (���������� ��ƾ�� ���������� ����)
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
       //���׸�Ʈ�� cnt�� ���

}
  
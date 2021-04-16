#include "7segment.h"

/*  
7-���׸�Ʈ�� ���Ǵ� ��Ʈ�� �ʱ�ȭ�Ѵ�.
*/
void init_7segment(void) 
{
  Pim.ddrh.byte = 0xFF;       //7segment as output port
  Pim.pth.byte = 0x00;      // 7 segment OFF
}

/*
  0~9 �߿� �ϳ��� ���� �Է��ϸ� �� ���� 7-���׸�Ʈ�� ����Ѵ�.
  */
void set_7segment(unsigned char number) 
{
  switch (number) 
  {
    case 0 : 
      Pim.pth.byte=(val0);		//7-���׸�Ʈ ���� '0'�� ��µǵ��� ��Ʈ ���� ����
      break;  
    case 1 : 
      Pim.pth.byte=(val1);		//7-���׸�Ʈ ���� '1'�� ��µǵ��� ��Ʈ ���� ����
      break;
    case 2 : 
      Pim.pth.byte=(val2);		//7-���׸�Ʈ ���� '2'�� ��µǵ��� ��Ʈ ���� ����
      break;
    case 3 : 
      Pim.pth.byte=(val3);		//7-���׸�Ʈ ���� '3'�� ��µǵ��� ��Ʈ ���� ����
      break;
    case 4 : 
      Pim.pth.byte=(val4);		//7-���׸�Ʈ ���� '4'�� ��µǵ��� ��Ʈ ���� ����
      break;
    case 5 : 
      Pim.pth.byte=(val5);		//7-���׸�Ʈ ���� '5'�� ��µǵ��� ��Ʈ ���� ����
      break;
    case 6 : 
      Pim.pth.byte=(val6);		//7-���׸�Ʈ ���� '6'�� ��µǵ��� ��Ʈ ���� ����
      break;
    case 7 : 
      Pim.pth.byte=(val7);		//7-���׸�Ʈ ���� '7'�� ��µǵ��� ��Ʈ ���� ����
      break;
    case 8 : 
      Pim.pth.byte=(val8);		//7-���׸�Ʈ ���� '8'�� ��µǵ��� ��Ʈ ���� ����
      break;                                        
    case 9 : 
      Pim.pth.byte=(val9);		//7-���׸�Ʈ ���� '9'�� ��µǵ��� ��Ʈ ���� ����
      break;
    case 10 :
      Pim.pth.byte=(0x00);		//7-���׸�Ʈ ���� �ҵ�Ǵ� ���� ����
      break;  
    default:
      break;
  }
  return; 
}

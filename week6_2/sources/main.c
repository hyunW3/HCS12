#include "main.h"
unsigned char RX[11]; 

/*RX[11]�� �ø��� ��� ���� ��ǻ�� ���̿� �ְ���� ���ڸ� �����ϴ� ������ ������ �Ѵ�.  �ִ� ���� �� �ִ� ���ڿ��� 11���� �����Ͽ���.*/

void main ()
{  
  init_LCD();
  int_disable();
  ini_interrupt();
  xint_enable();
  int_enable();
  init_sci0(19200,RX);    
/*�ø��� ��Ʈ�� �ʱ�ȭ �ϴ� �����̴�. bps�� 19200�̰� ���ڿ��� �ִ� ���̴� 10�̴�. */

  // ��Ʈ B�� ��Ʈ M�� ���� ����
  Regs.ddrb.byte = ( 0xFF );  // ��Ʈ B�� ��� ������� ����
  Pim.ddrm.byte = ( 0xC0 );   // ��Ʈ M�� 6,7�� ���� ������� ����
    
  // ��� LED ���α�
  Regs.portb.byte = ( 0xFE);   // ��Ʈ B�� ��� ���� 1�� ����
  Pim.ptm.byte = (  0xC0);      // ��Ʈ M�� 6,7�� ���� 1�� ���� 
  
  int_enable();
  write_char(0x80,'A');
	write_sci0("SCI OK");   // �������͹̳ο� "SCI OK" �޽��� ���
  for (;;);
}
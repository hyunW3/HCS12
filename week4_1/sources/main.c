#include "main.h"
#include <stdio.h>

void main ()
{
    init_LCD();         // LCD�� ����ϱ� ���� �ʱ�ȭ
    int_disable(); 
    ini_interrupt();
    xint_enable();
    int_enable();                             
    // 7 segment initialization
    Pim.ddrh.byte=0b11111111;        //output
    Pim.pth.byte = 0x00;             // NOT ON
    
    write_string((0x00), "Count = 0");   //LCD�� �ʱ�ȭ�� ǥ��
    
    for( ; ; );
}

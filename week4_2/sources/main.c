#include "main.h"
#include <stdio.h>

void main ()
{
    init_LCD();         // LCD�� ����ϱ� ���� �ʱ�ȭ
    int_disable(); 
    ini_interrupt();
    xint_enable();
    int_enable();       
    
    write_string((0x00), "Num1=0");   //LCD�� �ʱ�ȭ�� ǥ�� 
    write_string((0x08), "Num2=0");   //LCD�� �ʱ�ȭ�� ǥ�� � 
    write_string((0x40), "Result= ");   //LCD�� �ʱ�ȭ�� ǥ�
    
    for( ; ; );
}

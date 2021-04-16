#include "main.h"
#include <stdio.h>

void main ()
{
    init_LCD();         // LCD를 사용하기 위한 초기화
    int_disable(); 
    ini_interrupt();
    xint_enable();
    int_enable();                             
    // 7 segment initialization
    Pim.ddrh.byte=0b11111111;        //output
    Pim.pth.byte = 0x00;             // NOT ON
    
    write_string((0x00), "Count = 0");   //LCD에 초기화면 표시
    
    for( ; ; );
}

#include "led.h"
extern unsigned char RX[30];

/*
 INIT port used for LED
*/
void init_led(void)
{
  // 포트 B와 포트 M 을 출력으로 설정
  Regs.ddrb.byte = 0b11111111; 
  Pim.ddrm.byte = 0b11000000; 
  
  // 포트 B와 포트 M 에 연결된 모든 LED를 끔
  Regs.portb.byte = 0b11111111;
  Pim.ptm.byte = 0b11000000;
}
// 0 : ON , 1 : OFF

void set_led(unsigned int digit)
{

  unsigned char upper_digit, lower_digit;

  upper_digit = digit/256; // 10 비트 중에서 상위 2 비트의 값만 추출
  
  upper_digit = upper_digit<<6;	  // 포트 M의 6,7 번째 비트에서 LED가 출력 되기 때문에
                          // 위에서 추출한 상위 2 비트 값을 왼쪽으로 6비트 쉬프트 (ex. 00000011 -> 11000000)
  
  lower_digit = digit & 0b0011111111;    // 10 비트 중에서 하위 8 비트의 값만 추출

  Pim.ptm.byte = ~upper_digit;  // 상위 2비트의 값을 포트 M에 출력
  Regs.portb.byte = ~lower_digit; // 하위 8비트의 값을 포트 B에 출력                                       
  
}

void led_control(void){
  int i=0;
 unsigned char num=1;
 unsigned int num1=0;   // 1,2,3 cmd
 //if(RX[4] != '0') // error
 // RX[4:5] CMD_NUM RX[6] Data format
 if(RX[5]=='0' && RX[6] =='0'){ // INfO of LED to turn on
    //num = num<<(RX[7]-'0');
    if(RX[7] >= '8')  {
      num = num<<(RX[7]-'8'+6);
      Pim.ptm.byte &= ~num;
    }else {
       num = num<<(RX[7]-'0');
       Regs.portb.byte &= ~num;
    }
 }else if(RX[5] == '1' && RX[6]=='3'){  
   // RX[7:10] decimal num
   num1 = (RX[7]-'0')*1000+(RX[8]-'0')*100+(RX[9]-'0')*10+(RX[10]-'0');
   set_led(num1);
 }else if(RX[5] == '2' && RX[6]=='2'){ 
   // RX[7:9] hexadecimal
   for(i=0; i<3; i++){
    if(RX[7+i]>='A' && RX[7+i]<='F'){
     num1 += (RX[7+i]-'A'+10)<<((2-i)*4);  
    }else {
     num1 += (RX[7+i]-'0')<<((2-i)*4); 
    } 
   }
   set_led(num1);
 }else if(RX[5] == '3' && RX[6]=='4'){
  //RX[7:16] binary number
  for(i=0; i<10; i++){    
    if(RX[7+i]>='A' && RX[7+i]<='F'){
     num1 += (RX[7+i]-'A'+10)<<(9-i);  
    }else {
     num1 += (RX[7+i]-'0')<<(9-i); 
    } 
  } 
   set_led(num1);
 }else if(RX[5] == '4' && RX[6]=='0'){  
    if(RX[7] >= '8')  {
      num = num<<(RX[7]-'8'+6);
      Pim.ptm.byte |= num;
    }else {
       num = num<<(RX[7]-'0');
       Regs.portb.byte |= num;
    }
 
 }
  
  
 
 return;
 
}




#include "led.h"
extern unsigned char RX[30];

/*
 INIT port used for LED
*/
void init_led(void)
{
  // ��Ʈ B�� ��Ʈ M �� ������� ����
  Regs.ddrb.byte = 0b11111111; 
  Pim.ddrm.byte = 0b11000000; 
  
  // ��Ʈ B�� ��Ʈ M �� ����� ��� LED�� ��
  Regs.portb.byte = 0b11111111;
  Pim.ptm.byte = 0b11000000;
}
// 0 : ON , 1 : OFF

void set_led(unsigned int digit)
{

  unsigned char upper_digit, lower_digit;

  upper_digit = digit/256; // 10 ��Ʈ �߿��� ���� 2 ��Ʈ�� ���� ����
  
  upper_digit = upper_digit<<6;	  // ��Ʈ M�� 6,7 ��° ��Ʈ���� LED�� ��� �Ǳ� ������
                          // ������ ������ ���� 2 ��Ʈ ���� �������� 6��Ʈ ����Ʈ (ex. 00000011 -> 11000000)
  
  lower_digit = digit & 0b0011111111;    // 10 ��Ʈ �߿��� ���� 8 ��Ʈ�� ���� ����

  Pim.ptm.byte = ~upper_digit;  // ���� 2��Ʈ�� ���� ��Ʈ M�� ���
  Regs.portb.byte = ~lower_digit; // ���� 8��Ʈ�� ���� ��Ʈ B�� ���                                       
  
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




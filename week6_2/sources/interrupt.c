#include "interrupt.h"
#include <stdio.h>
char data[33];
int offset=0x80;
int full=0;
int i=0;
int j=0;
//int need_init =0;
char chr=65;
void init_LCDDATA(void);
/*************************************************/
/*  port J as interrupt.   */
/*************************************************/
void m_delay(unsigned int m);


void ini_interrupt(void){
 
 Pim.ddrj.byte=0b00000000;    // 인터럽트 포트의 방향 결정
 Pim.piej.byte=0xff;		// 인터럽트 포트의 인터럽트 enable
 Pim.ppsj.byte=0x00;		// 인터럽트 포트의 엣지 설정  
}
void interruptJ_function(void)
{   
  int index; 
  Regs.ddrb.byte = 0b11111111; 	// output init   
  // SW2 portJ 0pin, SW3 portJ 1pin
  if(Pim.pifj.byte & (0x01))      // SW2의 인터럽트 발생   
  {      
      // 'A' : 65, Z : 90, a : 97, z=122  
     // alphabet selection(next alphabet)
     if(chr == 90){   //'Z'
         chr= 97;   //'a'
     }else if(chr==122){  //'z'
        chr=65;
     }else {
        chr++;
     }
     write_char(offset+i+j,chr);
     Pim.pifj.byte |= 0x01;    // 인터럽트 플래그 초기화 
    
  } 
  else if(Pim.pifj.byte & (0x02	))  // SW3의 인터럽트 발생  portJ 1pin 
  {       
    if(i==0 &&j==0x00){
      for(index=32; index>=0; index--) data[index] = '\0'; 
    } 
      // select alphabet & next slot
      if(j==0x00 ) data[i++] = chr;
      else {
        data[16+i] = chr;
        i++;
      }
      if(i>15){
        if(j==0x00) j =0x40;
        else {
          j=0x00; // j==0x40 (2nd line) return to init
          full=1;
        }
        i=0; 
      }
      chr=65;
      write_char(offset+i+j,chr);
      Pim.pifj.byte |= 0x02;   // 인터럽트 플래그 초기화 
  }
    
}
void interruptX_function (void)    //XIRQ interrupt service func SW1 
{	 
   int index=0;
   if(j==0x40 ) i= i+17;
   if(i==0 && full==1) i = 32;
   for(index; index<i; index++){ 
    // 'A' : 65, Z : 90, a : 97, z=122  
    if(data[index]>=65 && data[index]<=90){
      data[index] = data[index] + 32; 
    }else {                        
      data[index] = data[index] - 32;  
    }
   }
   write_sci0(data); 
   m_delay(10);
   init_LCDDATA();

}
void init_LCDDATA(void){ 
  set_inst_register(CODE_CLR_DISP);
  offset=0x80;
//  need_init=1;
  i=0;
  j=0;
  full=0;
  chr=65;
  write_char(0x80,'A');
  
}
void m_delay(unsigned int m) 
{
 unsigned int i, j; 
 for(i=0;i<m;i++)
    for(j=0;j<2650;j++);  //16MHz : 1msec  

}

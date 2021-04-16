#include "main.h"                     
     
int ready =0;  
int interrupt_sw1 =0;
int interrupt_sw2 =0;
int interrupt_sw3 =0;         
unsigned char RX[30];
unsigned char TX[30];  
unsigned char CNT =0 ; // number of cnt 
unsigned char LED_CNT = 0; // num of LED ON
int expected_size[6]={1,2,3,4,10,16};
int data_size=0; // 0 : equal data size
void init_all(void);                       
void main ()
{
  int i;
  unsigned int tmp_num=1;
  int RX_len;
  //memcpy(RX,"11101110",11);                
  init_all();

           
  //write_string(0x00,"LCD ON");	
  write_sci0((unsigned char*) "SCI_OK\n");
  light7segment(0);
  set_led((unsigned int)0);  
	for (;;){
	 if(ready==1 && RX[0] =='<'){
	    for(RX_len=1; RX[RX_len-1]!='>'; RX_len++);
	    data_size = RX_len - (8+expected_size[RX[6]-'0']);
	    if(data_size >0){    
	        // overdatasize  
        sprintf(TX,"<0%c1000%d>",SYSTEM,0);      
        write_sci0(TX); 
	    }else if(data_size<0){  
	        // lossdatasize  
        sprintf(TX,"<0%c1000%d>",SYSTEM,1);      
        write_sci0(TX); 
	      
	    } 
	  // Group range check
	    if(RX[1] != '0' || !(RX[2] >= '0' && RX[2] <='5')) {
        sprintf(TX,"<0%c1000%d>",SYSTEM,2);      // overGroupCnt
        write_sci0(TX); 
	    }
    // Class range check
      if(!(RX[3] == '0' || RX[3] == '1')){  
        sprintf(TX,"<0%c1000%d>",SYSTEM,3);   // overClassCnt
        write_sci0(TX);
      }
    // Format range check
      if(!(RX[6] >= '0' && RX[6] <= '5')){  
        sprintf(TX,"<0%c1000%d>",SYSTEM,4);   // overFormatCnt
        write_sci0(TX);
      }
	    
	    // RX[1:2] group num , RX[3] CMD class, RX[4:5] CMD_NUM RX[6] Data format
      
      switch(RX[2]){  // group number  
        case LED:  
          // CMD range check   
	        if(RX[4] == '0' && (RX[5]>='0' && RX[5] <='4')) led_control();    
          else {   
            sprintf(TX,"<0%c1000%d>",SYSTEM,5);   // CantFindCmd_LED
            write_sci0(TX);
          }
          break;
        case LCD: 
          if(RX[4] == '0' && (RX[5]>='0' && RX[5] <='1')) LCD_control();   
          else {   
            sprintf(TX,"<0%c1000%d>",SYSTEM,6);   // CantFindCmd_LCD
            write_sci0(TX);
          }
          break;
        case SYSTEM:
          break;  
        default:
          set_led(1);
      }
  	   
	   /*
	   memset(RX,0,sizeof(char)*30); 
  	 ready=0;
  	 */
	 
  	//  write_string(LCD_LINE2,RX);
  	//  write_string(LCD_LINE1+8,RX_len);
  	  memset(RX,0,sizeof(char)*30);
  	  m_delay(1);
  	  ready=0;
  	
	 }
	
	 if(interrupt_sw1>0){
	      LED_CNT = 0;
	      tmp_num=1;
	      
	      for(i=0; i<8; i++){
	          if(~Regs.portb.byte & (tmp_num<<i)) LED_CNT++;
	      }
	      for(i=0; i<2; i++){
	          if(~Pim.ptm.byte & (tmp_num<<(i+6))) LED_CNT++;
	      }           
	      
	                       
        if(LED_CNT < 10) sprintf(TX,"<011000%d>",LED_CNT);
        else sprintf(TX,"<011000X>");
        write_sci0(TX);
        light7segment(LED_CNT);
        interrupt_sw1 = 0; 
	 }
	 
	 if(interrupt_sw2>0){ 
	      CNT++;                   
        if(CNT < 10) sprintf(TX,"<021000%d>",CNT);
        else sprintf(TX,"<021000X>");
        write_sci0(TX);
	        
        interrupt_sw2 = 0;
	 }
	 if(interrupt_sw3>0){ // sw3
	      i=get_atd0(0);		//ATD °ªÀ» ¹Þ¾Æ¿È
        sprintf(TX,"<0%c1000%d>",ADC,i);
        write_sci0(TX);
        interrupt_sw3 = 0; 
	 }
	  memset(TX,0,30);	 
	}
	
}
       
void init_all(void){ 
  int_disable(); 
  
  init_LCD();
  init_sci0(19200,RX);    // init serial port bps 19200, max length 10
  ini_interrupt(); // PORT B(LED) as output
  
  
  init_led();                     
  init_atd0(); 
  init_7segment(); 

  xint_enable();
  int_enable();
  
}
void m_delay(unsigned int m) //µô·¹ÀÌ ·çÆ¾
{
 unsigned int i, j; 
    
 //  disable_interrupt(); 
   
 for(i=0;i<m;i++)
    for(j=0;j<2650;j++);  //16MHz : 1msec  

 //   enable_interrupt();
}



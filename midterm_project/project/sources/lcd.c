// INSTRUCTION CODE
#include "lcd.h"
extern unsigned char RX[30];

void init_LCD(void)
{
    Regs.ddra.byte = 0x7F;  // 포트 A의 0~6번 핀의 방향을 출력으로 설정
    // 데이터 길이 4비트, 2줄 표시 설정
    set_inst_register(CODE_FUNC_SET(0, 1, 0));
    // display ON?, cursor?(ON) cursor blink(ON) set
    set_inst_register(CODE_DISP_CTRL(1, 1, 1));
    // Incremental mode(default = Decrement), Entire shift off   
    set_inst_register(CODE_ENTRY_MODE_SET(0, 0));
    // Clear Display
    set_inst_register(CODE_CLR_DISP);
}

// IR 레지스터에 값을 설정하여 LCD에 명령을 내림
void set_inst_register(BYTE code)
{
    // 명령 코드의 상위 4비트를 보냄
    // 포트 A의 8번째 비트는 바꾸지 않음 (LCD에서 쓰이지 않음)
    Regs.porta.byte = ((code&0xF0)>>1)|0x04|(Regs.porta.byte&0x80);
    DISABLE_LCD();
    // 명령 코드의 하위 4비트를 보냄
    Regs.porta.byte = ((code&0x0F)<<3)|0x04|(Regs.porta.byte&0x80);
    DISABLE_LCD();
    ms_delay(1);
}

// LCD의 RAM에 데이터를 씀
void write_data(BYTE data)
{
    // 데이터의 상위 4비트를 보냄
    Regs.porta.byte = ((data&0xF0)>>1)|0x01|0x04|(Regs.porta.byte&0x80);
    DISABLE_LCD();
    // 데이터의 하위 4비트를 보냄
    Regs.porta.byte = ((data&0x0F)<<3)|0x01|0x04|(Regs.porta.byte&0x80);
    DISABLE_LCD();
    ms_delay(1);
}

// LCD의 특정 위치에 문자열을 씀
void write_string(BYTE offset, char *str)
{   
    int i;
    // 문자열을 쓸 주소 설정
    set_inst_register(CODE_SET_DDRAM_ADDR(offset));
    for (i = 0; str[i] != '\0'; i++) {
        write_data(str[i]);
    }
}
void write_char(BYTE offset, char chr)
{   
    set_inst_register(CODE_SET_DDRAM_ADDR(offset));
    write_data(chr);
    //set_inst_register(CODE_CUR_DISP_SHIFT(0,1)); 
}
// ms 단위로 시간을 지연시키는 함수
void ms_delay(unsigned int ms) 
{
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j=0; j < 2650; j++);     // 아무것도 하지 않으면서 시간 지연
    }
}
void LCD_control(void){
   if(RX[3] == '0'){    // CMD_CLASS control case
       // D16 
     if(RX[6] == '5'){  // DATA format D16
        // RX[7:22]
        RX[23] = '\0';
        if(RX[4] == '0' && RX[5] == '0'){  // lower line (top)
          write_string(LCD_LINE1,RX+7);
        }else if(RX[4] == '0' && RX[5] == '1'){ // high line (bottom)
          write_string(LCD_LINE2,RX+7);
        }
     }
    
   }
  
}
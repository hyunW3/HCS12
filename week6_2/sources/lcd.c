// INSTRUCTION CODE
#include "lcd.h"


void init_LCD(void)
{
    Regs.ddra.byte = 0x7F;  // ∆˜∆Æ A¿« 0~6π¯ «…¿« πÊ«‚¿ª √‚∑¬¿∏∑Œ º≥¡§
    // µ•¿Ã≈Õ ±Ê¿Ã 4∫Ò∆Æ, 2¡Ÿ «•Ω√ º≥¡§
    set_inst_register(CODE_FUNC_SET(0, 1, 0));
    // display ON√, cursor≠(ON) cursor blink(ON) set
    set_inst_register(CODE_DISP_CTRL(1, 1, 1));
    // Incremental mode(default = Decrement), Entire shift off   
    set_inst_register(CODE_ENTRY_MODE_SET(0, 0));
    // Clear Display
    set_inst_register(CODE_CLR_DISP);
}

// IR ∑π¡ˆΩ∫≈Õø° ∞™¿ª º≥¡§«œø© LCDø° ∏Ì∑…¿ª ≥ª∏≤
void set_inst_register(BYTE code)
{
    // ∏Ì∑… ƒ⁄µÂ¿« ªÛ¿ß 4∫Ò∆Æ∏¶ ∫∏≥ø
    // ∆˜∆Æ A¿« 8π¯¬∞ ∫Ò∆Æ¥¬ πŸ≤Ÿ¡ˆ æ ¿Ω (LCDø°º≠ æ≤¿Ã¡ˆ æ ¿Ω)
    Regs.porta.byte = ((code&0xF0)>>1)|0x04|(Regs.porta.byte&0x80);
    DISABLE_LCD();
    // ∏Ì∑… ƒ⁄µÂ¿« «œ¿ß 4∫Ò∆Æ∏¶ ∫∏≥ø
    Regs.porta.byte = ((code&0x0F)<<3)|0x04|(Regs.porta.byte&0x80);
    DISABLE_LCD();
    ms_delay(1);
}

// LCD¿« RAMø° µ•¿Ã≈Õ∏¶ æ∏
void write_data(BYTE data)
{
    // µ•¿Ã≈Õ¿« ªÛ¿ß 4∫Ò∆Æ∏¶ ∫∏≥ø
    Regs.porta.byte = ((data&0xF0)>>1)|0x01|0x04|(Regs.porta.byte&0x80);
    DISABLE_LCD();
    // µ•¿Ã≈Õ¿« «œ¿ß 4∫Ò∆Æ∏¶ ∫∏≥ø
    Regs.porta.byte = ((data&0x0F)<<3)|0x01|0x04|(Regs.porta.byte&0x80);
    DISABLE_LCD();
    ms_delay(1);
}

// LCD¿« ∆Ø¡§ ¿ßƒ°ø° πÆ¿⁄ø≠¿ª æ∏
void write_string(BYTE offset, char *str)
{   
    int i;
    // πÆ¿⁄ø≠¿ª æµ ¡÷º“ º≥¡§
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
// ms ¥‹¿ß∑Œ Ω√∞£¿ª ¡ˆø¨Ω√≈∞¥¬ «‘ºˆ
void ms_delay(unsigned int ms) 
{
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j=0; j < 2650; j++);     // æ∆π´∞Õµµ «œ¡ˆ æ ¿∏∏Èº≠ Ω√∞£ ¡ˆø¨
    }
}
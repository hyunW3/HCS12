#ifndef INTERRUPT_H        /*prevent duplicated includes*/
#define INTERRUPT_H
#define xint_enable() {asm andcc #0xBF;}

#define val0 0X7F  
#define val1 0X06
#define val2 0X5B 
#define val3 0X4F 
#define val4 0X66
#define val5 0X6D
#define val6 0X7D
#define val7 0X27 
#define val8 0X7F
#define val9 0X67


/*Includes*/
#include "projectglobals.h"
#include "lcd.h"

void ini_interrupt(void);
void interruptJ_function(void);
void interruptX_function(void);  

#endif 

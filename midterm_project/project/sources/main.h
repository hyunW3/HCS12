#ifndef MAIN_H        /*prevent duplicated includes*/
#define MAIN_H

#include "projectglobals.h"
#include "atd.h"
#include "lcd.h"
#include "led.h"
#include "sci.h"     
#include "7segment.h"
#include "stdlib.h"
#include "stdio.h"
#include <string.h>


//group number
#define LED     '0'
#define SEGMENT '1'
#define SWITCH  '2'      
#define LCD     '3'
#define ADC     '4'
#define SYSTEM  '5'

//Format name
#define D1  '0'   // 1B
#define D2  '1'   // 2B
#define D3  '2'   // 3B
#define D4  '3'   // 4B
#define D10 '4'   // 10B
#define D16 '5'  // 16B

void m_delay(unsigned int m);
#endif /*MAIN_H*/
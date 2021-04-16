#ifndef LED_H        /*prevent duplicated includes*/
#define LED_H

/*Includes*/
#include "projectglobals.h"

void init_led(void);
void set_led(unsigned int digit);  
void led_control(void);
#endif /* LED_H */
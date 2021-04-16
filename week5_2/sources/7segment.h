#ifndef SEGMENT_H        /*prevent duplicated includes*/
#define SEGMENT_H

/*Includes*/
#include "projectglobals.h"

void init_7segment(void);
void set_7segment(unsigned char number);
  
#define val0 0X3F  
#define val1 0X06
#define val2 0X5B 
#define val3 0X4F 
#define val4 0X66
#define val5 0X6D
#define val6 0X7D
#define val7 0X27 
#define val8 0X7F
#define val9 0X67

#endif /* SEGMENT_H */
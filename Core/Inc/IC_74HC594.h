#ifndef __IC_74HC594_H
#define __IC_74HC594_H

#ifdef __cplusplus
extern "C" {
#endif


#include "gpio.h" 
void ic_74HC594_init(void);
void LED74HC594(int positon, int num);
void quetled(int num);



#ifdef __cplusplus
}
#endif

#endif 
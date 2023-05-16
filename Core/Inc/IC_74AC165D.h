#ifndef __IC_74AC165D_H
#define __IC_74AC165D_H

#ifdef __cplusplus
extern "C" {
#endif


#include "gpio.h"
void ic_74AC165D_init(void);
uint8_t shiftIn(void);

extern uint8_t data;


#ifdef __cplusplus
}
#endif

#endif 
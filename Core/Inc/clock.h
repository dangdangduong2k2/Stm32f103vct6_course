#ifndef __CLOCK_H
#define __CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"

  
  
void SystemClock_Config(void);
void system_clock_peripheral_init(void);

  


#ifdef __cplusplus
}
#endif

#endif 
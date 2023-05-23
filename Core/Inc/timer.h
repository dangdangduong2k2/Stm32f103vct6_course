#ifndef __TIMER_H
#define __TIMER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"
 
void timer1_Init(void);
void timer2_Init(void);
void timer3_Init(void);
void set_pwm(uint8_t channel, uint16_t pwm);
uint16_t get_pwm(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif 
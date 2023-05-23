#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif


#include "stm32f1xx_hal.h"
void uart1_init(void);
void uart_sendchar(uint8_t ch);
void uart_sendstring(const char* str);
int convert(const char* chuoi);
typedef struct
{
    uint8_t data;
    uint8_t index;
    
    uint8_t buffer[5];
    
} uart1;

extern uart1 Uart1;

#ifdef __cplusplus
}
#endif

#endif 
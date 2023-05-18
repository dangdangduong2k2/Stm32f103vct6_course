#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "IC_74AC165D.h"
#include "IC_74HC594.h" 
#include "LCD_Lib.h"
#include "uart.h"
#include <stdio.h>



uint32_t time20ms = 0;
int num=0;
int state1;
int state2;
CLCD_Name LCD1;
char lcd_send[16];

char datauart;
char buffer[6];
uint8_t index = 0;
uint8_t state =0;

void TIM1_UP_IRQHandler(void)
{

    if (++ time20ms > 20)
    {
        time20ms = 0;
        
    }
    else
    {
        
    }
    
    TIM1->SR &= ~(TIM_SR_UIF);
}

void USART1_IRQHandler(void) 
{
    if (USART1->SR & USART_SR_RXNE) 
    {
        datauart = USART1->DR;
        if (datauart == 0x0A) 
        {    
            index = 0;
            
        } 
        else 
        {
            buffer[index++] = datauart;
            if (index >= 5) 
            {  
                index = 0;
            }
        }
    } 
}

int main(void)
{
 
  //system config:

    //HAL
    HAL_Init();
    //system clock
    SystemClock_Config();
    //system peripheral
    system_clock_peripheral_init();
    //timer init
    timer1_Init();
    timer2_Init();
  uart1_init();
    
    
  //user config:
  
    //ic I/O
    ic_74AC165D_init();
    //led 7 
    ic_74HC594_init();
    //I/O init:
    gpio_init(GPIOD,0,0);
    gpio_init(GPIOD,1,0);
    gpio_init(GPIOD,2,0);
    gpio_init(GPIOD,3,0);
    gpio_init(GPIOD,4,0);
    gpio_init(GPIOD,5,0);
    gpio_init(GPIOD,6,0);
    gpio_init(GPIOD,7,0);
    gpio_write(GPIOD,4,1);
    //lcd init
    CLCD_4BIT_Init(&LCD1, 16, 2,
                                GPIOD, GPIO_PIN_7, GPIOD, GPIO_PIN_5,
                                GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1,
                                GPIOD, GPIO_PIN_2, GPIOD, GPIO_PIN_3);
    //uart1 init
    uart1_init();
while (1)
{

//        shiftIn();
//        if((data&(1<<0))== 0 && state1==0)
//        {   
//          num++;
//          state1=1;
//        }
//        if((data&(1<<5))== 0 && state2==0)
//        {
//          num--;
//          state2=1;
//        }
//        
//        if((data&(1<<0))==1 )
//        {
//          state1=0;
//        }
//        if((data&(1<<5))==(1<<5))
//        {
//          state2=0;
//        } 
//        quetled(num);
//        
//        CLCD_SetCursor(&LCD1,0,0);
//        CLCD_WriteString(&LCD1,"kkkkk");
//        sprintf(lcd_send,"lcd dem :%d",TIM2->CCR3);
//        CLCD_SetCursor(&LCD1,0,1);
//        CLCD_WriteString(&LCD1,lcd_send);
}
  
}






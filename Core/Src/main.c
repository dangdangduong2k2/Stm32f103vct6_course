#include "main.h"
#include "clock.h"
#include "gpio.h"
#include "timer.h"
#include "IC_74AC165D.h"
#include "IC_74HC594.h" 
#include "LCD_Lib.h"
#include "uart.h"
#include <stdio.h>

//timer
uint32_t time20ms = 0;
//button, 7seg
int num=0;
int state1;
int state2;
int16_t muma;
//LCD
CLCD_Name LCD1;
char lcd_send[16];
//uart
uart1 Uart1;
char  buff[2];

//timer interrupt
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
//uart interrupt
void USART1_IRQHandler(void) 
{
    if (USART1->SR & USART_SR_RXNE) 
    {
        Uart1.data = USART1->DR;
        if (Uart1.data == 0x0A) //enter
        {    
            Uart1.index = 0;
            
        } 
        else 
        {
            Uart1.buffer[Uart1.index++] = Uart1.data;
            if (Uart1.index >= 5) 
            {  
                Uart1.index = 0;
            }
        }
        int temp0 = Uart1.buffer[0]-'0';
        int temp1 = Uart1.buffer[1]-'0';
        num=temp0*10+temp1;
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
    //uart1 init
    uart1_init();
    
    
  //user config:
  
    //ic I/O
    ic_74AC165D_init();
    //led 7 
    ic_74HC594_init();
    //I/O init:
    
    //lcd setup
    gpio_init(GPIOD,0,0);
    gpio_init(GPIOD,1,0);
    gpio_init(GPIOD,2,0);
    gpio_init(GPIOD,3,0);
    gpio_init(GPIOD,4,0);
    gpio_init(GPIOD,5,0);
    gpio_init(GPIOD,6,0);
    gpio_init(GPIOD,7,0);
    
    gpio_write(GPIOD,4,1);
    
    CLCD_4BIT_Init(&LCD1, 16, 2,
    GPIOD, GPIO_PIN_7, GPIOD, GPIO_PIN_5,
    GPIOD, GPIO_PIN_0, GPIOD, GPIO_PIN_1,
    GPIOD, GPIO_PIN_2, GPIOD, GPIO_PIN_3);
    
while (1)
{
#if(1)
        shiftIn();
        if(num>99)
        {
          num=0;
        }
        if(num<0)
        {
          num=99;
        }
        if((data&(1<<0))== 0 && state1==0)
        {   
            num++;
            state1=1;            
            if(num>99)
            {
              num=0;
            }
            sprintf(buff, "%d\n", num);
            uart_sendstring(buff);
        }
        if((data&(1<<5))== 0 && state2==0)
        {
            num--;
            state2=1;
            if(num<0)
            {
              num=99;
            }
            sprintf(buff, "%d\n", num);
            uart_sendstring(buff);
        }
        
        if((data&(1<<0))==1 )
        {
          state1=0;
        }
        if((data&(1<<5))==(1<<5))
        {
          state2=0;
        } 
        
        quetled(num);
#endif
        
#if(0)  
        CLCD_SetCursor(&LCD1,0,0);
        CLCD_WriteString(&LCD1,"kkkkk");
        sprintf(lcd_send,"lcd dem :%d",TIM2->CCR3);
        CLCD_SetCursor(&LCD1,0,1);
        CLCD_WriteString(&LCD1,lcd_send);
#endif
}
  
}






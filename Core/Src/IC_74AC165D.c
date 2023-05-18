#include "IC_74AC165D.h"
#include "gpio.h"


#define CLK_PIN 3
#define CLK_PORT GPIOB

#define LOAD_PIN 1
#define LOAD_PORT GPIOE

#define DATA_PIN 4
#define DATA_PORT GPIOB

 uint8_t data;
void ic_74AC165D_init(void)
{
    gpio_init(CLK_PORT,CLK_PIN,0);//B3 output
    gpio_init(LOAD_PORT,LOAD_PIN,0);//E1 output
    gpio_init(DATA_PORT,DATA_PIN,1);//E4 input
}

uint8_t shiftIn(void)
{
    data = 0;
    gpio_write(LOAD_PORT, LOAD_PIN,0); 
    gpio_write(LOAD_PORT, LOAD_PIN,1);
    for (int i = 7; i >= 0; i--)
    {
        gpio_write(CLK_PORT, CLK_PIN,0);  
        data |= (gpio_read(DATA_PORT, DATA_PIN) << i);
        gpio_write(CLK_PORT, CLK_PIN,1);
    }
    return data;
    
}
#include "IC_74HC594.h" 


#define CLK_PIN 3
#define CLK_PORT GPIOB

#define LATCH_PIN 0
#define LATCH_PORT GPIOE

#define DATA_PIN 5
#define DATA_PORT GPIOB

unsigned char led_position[5] = { 0x08, 0x10,0x20,0x40,0x80};  //LED position
unsigned char led_code[10] = {0xAF, 0xA0, 0x6E, 0xEA, 0xE1, 0xCB, 0xCF, 0xA2, 0xEF, 0xEB};// 0->9


void ic_74HC594_init(void)
{
    gpio_init(CLK_PORT,CLK_PIN,0);//B3 output
    gpio_init(LATCH_PORT,LATCH_PIN,0);//E1 output
    gpio_init(DATA_PORT,DATA_PIN,0);//E4 input
}

void LED74HC594(char data){
	for(char i=0;i<=7;i++){
		if((data&(1<<(7-i)))==0){
                    gpio_write(DATA_PORT,DATA_PIN,0);     
		}
		else{
                    gpio_write(DATA_PORT,DATA_PIN,1); 
		}
		gpio_write(CLK_PORT,CLK_PIN,0);  
                gpio_write(CLK_PORT,CLK_PIN,1);  
                
	}
        gpio_write(LATCH_PORT,LATCH_PIN,1);  
        gpio_write(LATCH_PORT,LATCH_PIN,0);  
        
}


void quetled(char tram, char chuc, char dv)
{
	for (char i = 0; i<=2;i++)
	{
		LED74HC594(led_position[2]);
		LED74HC594(led_code[tram]);
		HAL_Delay(1);
		
		LED74HC594(led_position[3]);
		LED74HC594(led_code[chuc]);
		HAL_Delay(1);

		LED74HC594(led_position[4]);
		LED74HC594(led_code[dv]);
		HAL_Delay(1);
	}
}

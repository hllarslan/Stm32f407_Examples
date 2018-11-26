#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f4xx_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC

/* Definition for each led
 */
#define led_a  (GPIO_Pin_12)
#define led_b  (GPIO_Pin_11)
#define led_c  (GPIO_Pin_8)
#define led_d  (GPIO_Pin_9)
#define led_e  (GPIO_Pin_10)
#define led_f  (GPIO_Pin_13)
#define led_g  (GPIO_Pin_14)

/* Definition of all led sequences for digits
 */
#define All_Leds   (led_a | led_b | led_c | led_d | led_e | led_f | led_g )

#define Zero  ((All_Leds) & ~(led_g))
#define One   ( led_b | led_c)
#define Two   ((All_Leds) & ~ (led_c | led_f))
#define Three ((All_Leds) & ~ (led_e | led_f))
#define Four  ( led_b | led_g | led_f | led_c )
#define Five  ((All_Leds) & ~ (led_b | led_e))
#define Six   ((All_Leds) & ~(led_b))
#define Seven ( led_a | led_b | led_c)
#define Eight ( All_Leds)
#define Nine  ((Four) | led_d | led_a)

int main(){
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_InitTypeDef GPIO_SegInit;
	
	/* Gpio configuration for Port E, Pins of 
	 * 8-14
	 */
	GPIO_SegInit.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_SegInit.GPIO_Pin   = All_Leds;
	GPIO_SegInit.GPIO_OType = GPIO_OType_PP;
	GPIO_SegInit.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_SegInit.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOE, &GPIO_SegInit);
	
	GPIO_SetBits(GPIOE, Nine);
	
	
	while(1);
}

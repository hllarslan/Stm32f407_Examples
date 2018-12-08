#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f4xx_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f4xx_syscfg.h"           // Keil::Device:StdPeriph Drivers:SYSCFG
#include "stm32f4xx_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f4xx_tim.h"              // Keil::Device:StdPeriph Drivers:TIM



void Configure_EXTI_PD0(void){
	
	/* Started first by clearing pending bit to be
	 * sure no interrupt is triggered accidentally
	 */
	EXTI_ClearITPendingBit(EXTI_Line0);
	
	/* Enabling Clocks for GPIOD to use external button
	 * connected to D0 pin and SYSCFG to handle config
	 * of EXTI
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitTypeDef GPIO_Struct;
	EXTI_InitTypeDef EXTI_Struct;
	NVIC_InitTypeDef NVIC_Struct;
	
	/* Button is configured as pull down, input 
	 * and connected to a D0 pin 
	 */
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Pin   = GPIO_Pin_0;
	GPIO_Struct.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOD, &GPIO_Struct);
	
	/* For GPIOD pin 0 below line should be used 
	 * to select appropriate EXTI line for pin
	 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);
	
	/* EXTI configuration for line0 since D0 will be using
	 */
	EXTI_Struct.EXTI_Line    = EXTI_Line0;
	EXTI_Struct.EXTI_LineCmd = ENABLE;
	EXTI_Struct.EXTI_Mode    = EXTI_Mode_Interrupt;
	EXTI_Struct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	
	EXTI_Init(&EXTI_Struct);
	
	/* For this simple button interrupt priority is
	 * not that important
	 */
	 
	NVIC_Struct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_Struct.NVIC_IRQChannelSubPriority        = 0x00;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_Struct);
	
	

}

void EXTI0_IRQHandler(void){
	
	/* When button interrupt is received first blink
	 * the onboard led D13 then wait until button 
	 * released and if released blink off led
	 * Finally, clearing Pending bit to complete
	 * interrupt so that upcoming interrupts will work
	 * without problem
	 */
	if((EXTI_GetITStatus(EXTI_Line0) != RESET) ){
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		
		while(GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_0));
		
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
		
		
}
	
int main(){
	
	Configure_EXTI_PD0();
	
	
	/* Onboard led configuration to blink
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitTypeDef GPIO_Struct;
	
	
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_Pin = GPIO_Pin_13;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOD, &GPIO_Struct);
	
	while(1){
		
	}

}

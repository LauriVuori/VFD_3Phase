/*This code tests NUCLEO-L152RE board transmitter UART communication by using
9600 BAUD and float print with sprintf
*/

/* Includes */
#include "include.h"
#include "nucleo152start.h"
/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

void delay_Ms(int delay);
void init_PWM_TIM2(void);
void init_PWM_TIM8(void);
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void) {
	/* Configure the system clock to 32 MHz and update SystemCoreClock */
	SetSysClock();
	SystemCoreClockUpdate();
	USART2_Init();
	init_PWM_TIM2();


	/* Infinite loop */
	while (1) {
		TIM2->CCR1 = TIM2->CCR1 * 110 / 100;
		if (TIM2->CCR1 > 1000) {
			TIM2->CCR1 = 10;
		}
	}
	return 0;
}

void init_PWM_TIM2(void) {
	// AHB peripheral clock enable register
	RCC->AHBENR |= 1;				// Enable GPIOA clock
	// GPIO alternate function low register (GPIOx_AFRL) 
	GPIOA->AFR[0] |= 0x00100000; 	// PA5 pin for tim2
	// GPIO port mode register (GPIOx_MODER) (x = A..H)
	GPIOA->MODER &= ~0x0000C00;		// Clear bits
	GPIOA->MODER |= 0x0000800;		// Set bits

	//Setup TIM2
	// APB1 peripheral clock enable register
	RCC->APB1ENR |= 1; 				// Enable TIM2 clock
	// TIMx prescaler (TIMx_PSC)
	TIM2->PSC = 16000 - 1;				// divided by 10
	// TIMx auto-reload register
	TIM2->ARR = 1000 - 1; 			// divided by 26667
	// TIMx counter (TIMx_CNT)
	TIM2->CNT = 0;
	// TIMx capture/compare mode register 1 	
	TIM2->CCMR1 = 0x0060; 			// PWM mode
	// TIMx capture/compare enable register (TIMx_CCER)
	TIM2->CCER = 1;					// Enable PWM Ch1
	// TIMx capture/compare register 1 
	TIM2->CCR1 = 8889 - 1; 			// Pulse width 1/3 of the period
	// TIMx control register 1
	TIM2->CR1 = 1;					// Enable Timer
}

void delay_Ms(int delay)
{
	int i=0;
	for(; delay>0;delay--)
		for(i=0;i<2460;i++); //measured with oscilloscope
}

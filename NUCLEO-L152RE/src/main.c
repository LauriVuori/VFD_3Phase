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
void init_PWM_TIM3(void);
void init_PWM_TIM4(void);
void init_PWM_TIM9(void);
void debug_APB1_TIM2_freeze(void);
void debug_APB1_TIM2_unfreeze(void);
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
	init_PWM_TIM3();
	init_PWM_TIM4();

	// debug_APB1_TIM2_unfreeze();
	debug_APB1_TIM2_freeze();

	/* Infinite loop */
	while (1) {
		TIM2->CCR1 += 10;
		TIM3->CCR1 += 10;
		TIM4->CCR1 += 10;
		if (TIM2->CCR1 > 2000) {
			TIM2->CCR1 = 10;
			TIM4->CCR1 = 10;

			
		}
		if (TIM3->CCR1 > 2000) {
			TIM3->CCR1 = 10;
		}
	}
	return 0;
}
void debug_APB1_TIM2_unfreeze(void) {
	DBGMCU->APB1FZ &= ~1;
}
void debug_APB1_TIM2_freeze(void) {
	// Debug MCU APB1 freeze register
	DBGMCU->APB1FZ |= 1;
}

//dont work
void init_PWM_TIM9(void) {
	// AHB peripheral clock enable register
	RCC->AHBENR |= 1;				// Enable GPIOA clock
	// GPIO alternate function low register (GPIOx_AFRL) 
	// AF03
	GPIOA->AFR[0] |= ((1 << 29) | (1 << 28));  	// PA7 pin for TIM9
	// GPIO port mode register (GPIOx_MODER) (x = A..H)
	GPIOA->MODER &= ~((1<< 14) | (1 << 15));		// Clear bits
	GPIOA->MODER |= (1 << 15);		// Set bits


	//Setup TIM9
	// APB1 peripheral clock enable register
	RCC->APB2ENR |= (2 << 1); 		// Enable TIM9 clock
	// TIMx prescaler (TIMx_PSC)
	TIM9->PSC = 32000 - 1;			// divided by 16000
	// TIMx auto-reload register
	TIM9->ARR = 2000 - 1; 			// divided by 26667
	// TIMx counter (TIMx_CNT)
	TIM9->CNT = 0;
	// TIMx capture/compare mode register 1 	
	TIM9->CCMR1 = 0x0060; 			// PWM mode
	// TIMx capture/compare enable register (TIMx_CCER)
	TIM9->CCER = 1;					// Enable PWM Ch1
	// TIMx capture/compare register 1 
	TIM9->CCR1 = 10 - 1; 			// Pulse width 1/3 of the period
	// TIMx control register 1
	TIM9->CR1 = 1;					// Enable Timer	
}


void init_PWM_TIM4(void) {
	// AHB peripheral clock enable register
	RCC->AHBENR |= (1 << 1);				// Enable GPIOB clock
	// GPIO alternate function low register (GPIOx_AFRL) 
	GPIOB->AFR[0] |= (1 << 25);   			// PB6 pin for tim4
	// GPIO port mode register (GPIOx_MODER) (x = A..H)
	GPIOB->MODER &= ~((1<< 13) | (1 << 12));// Clear bits
	GPIOB->MODER |= (1 << 13);				// Set bits

	//Setup TIM4
	// APB1 peripheral clock enable register
	RCC->APB1ENR |= (2 << 1); 		// Enable TIM4 clock
	// TIMx prescaler (TIMx_PSC)
	TIM4->PSC = 8000 - 1;			// divided by 16000
	// TIMx auto-reload register
	TIM4->ARR = 2000 - 1; 			// divided by 26667
	// TIMx counter (TIMx_CNT)
	TIM4->CNT = 0;
	// TIMx capture/compare mode register 1 	
	TIM4->CCMR1 = 0x0060; 			// PWM mode
	// TIMx capture/compare enable register (TIMx_CCER)
	TIM4->CCER = 1;					// Enable PWM Ch1
	// TIMx capture/compare register 1 
	TIM4->CCR1 = 10 - 1; 			// Pulse width 1/3 of the period
	// TIMx control register 1
	TIM4->CR1 = 1;					// Enable Timer	
}
// not working atm
// void init_PWM_TIM4(void) {
// 	// AHB peripheral clock enable register
// 	RCC->AHBENR |= 1;				// Enable GPIOA clock
// 	// GPIO alternate function low register (GPIOx_AFRL) 
// 	GPIOA->AFR[1] |= (1 << 5);  	// PA7 pin for tim4
// 	// GPIO port mode register (GPIOx_MODER) (x = A..H)
// 	GPIOA->MODER &= ~((1<< 14) | (1 << 15));		// Clear bits
// 	GPIOA->MODER |= (1 << 19);		// Set bits

// 	//Setup TIM4
// 	// APB1 peripheral clock enable register
// 	RCC->APB1ENR |= (2 << 1); 		// Enable TIM4 clock
// 	// TIMx prescaler (TIMx_PSC)
// 	TIM4->PSC = 32000 - 1;			// divided by 16000
// 	// TIMx auto-reload register
// 	TIM4->ARR = 2000 - 1; 			// divided by 26667
// 	// TIMx counter (TIMx_CNT)
// 	TIM4->CNT = 0;
// 	// TIMx capture/compare mode register 1 	
// 	TIM4->CCMR1 = 0x0060; 			// PWM mode
// 	// TIMx capture/compare enable register (TIMx_CCER)
// 	TIM4->CCER = 1;					// Enable PWM Ch1
// 	// TIMx capture/compare register 1 
// 	TIM4->CCR1 = 10 - 1; 			// Pulse width 1/3 of the period
// 	// TIMx control register 1
// 	TIM4->CR1 = 1;					// Enable Timer	
// }

void init_PWM_TIM3(void) {
	// AHB peripheral clock enable register
	RCC->AHBENR |= 1;				// Enable GPIOA clock
	// GPIO alternate function low register (GPIOx_AFRL) 
	GPIOA->AFR[0] |= (1 << 25); 	// PA6 pin for tim3


	// GPIO port mode register (GPIOx_MODER) (x = A..H)
	GPIOA->MODER &= ~((1<< 13) | (1 << 12));		// Clear bits
	GPIOA->MODER |= (1 << 13);		// Set bits

	//Setup TIM3
	// APB1 peripheral clock enable register
	RCC->APB1ENR |= (1 << 1); 		// Enable TIM3 clock
	// TIMx prescaler (TIMx_PSC)
	TIM3->PSC = 32000 - 1;			// divided by 16000
	// TIMx auto-reload register
	TIM3->ARR = 2000 - 1; 			// divided by 26667
	// TIMx counter (TIMx_CNT)
	TIM3->CNT = 0;
	// TIMx capture/compare mode register 1 	
	TIM3->CCMR1 = 0x0060; 			// PWM mode
	// TIMx capture/compare enable register (TIMx_CCER)
	TIM3->CCER = 1;					// Enable PWM Ch1
	// TIMx capture/compare register 1 
	TIM3->CCR1 = 10 - 1; 			// Pulse width 1/3 of the period
	// TIMx control register 1
	TIM3->CR1 = 1;					// Enable Timer	
}

void init_PWM_TIM2(void) {
	// AHB peripheral clock enable register
	RCC->AHBENR |= 1;				// Enable GPIOA clock
	// GPIO alternate function low register (GPIOx_AFRL) 
	// GPIOA->AFR[0] |= 0x00100000; 	// PA5 pin for tim2
	GPIOA->AFR[0] |= (1 << 20);
	// GPIO port mode register (GPIOx_MODER) (x = A..H)
	GPIOA->MODER &= ~0x0000C00;		// Clear bits
	GPIOA->MODER |= (1 << 11);		// Set bits

	//Setup TIM2
	// APB1 peripheral clock enable register
	RCC->APB1ENR |= 1; 				// Enable TIM2 clock
	// TIMx prescaler (TIMx_PSC)
	TIM2->PSC = 16000 - 1;				// divided by 16000
	// TIMx auto-reload register
	TIM2->ARR = 2000 - 1; 			// divided by 26667
	// TIMx counter (TIMx_CNT)
	TIM2->CNT = 0;
	// TIMx capture/compare mode register 1 	
	TIM2->CCMR1 = 0x0060; 			// PWM mode
	// TIMx capture/compare enable register (TIMx_CCER)
	TIM2->CCER = 1;					// Enable PWM Ch1
	// TIMx capture/compare register 1 
	TIM2->CCR1 = 10 - 1; 			// Pulse width 1/3 of the period
	// TIMx control register 1
	TIM2->CR1 = 1;					// Enable Timer
}

void delay_Ms(int delay)
{
	int i=0;
	for(; delay>0;delay--)
		for(i=0;i<2460;i++); //measured with oscilloscope
}

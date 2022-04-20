#include "timers.h"

/**
 * @brief Init Timer 4 PWM, 16kHz, PB6
 * 
 * 
 */

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
	TIM4->PSC = TIM4_PRESCALER_VAL - 1;			// divided by 16000
	// TIMx auto-reload register
	TIM4->ARR = TIM4_ARR_REGISTER - 1; 			// divided by 26667
	// TIMx counter (TIMx_CNT)
	TIM4->CNT = 0;
	// TIMx capture/compare mode register 1
	TIM4->CCMR1 = 0x0060; 			// PWM mode
	// TIMx capture/compare enable register (TIMx_CCER)
	TIM4->CCER = 1;					// Enable PWM Ch1
	// TIMx capture/compare register 1
	TIM4->CCR1 = TIM2_DUTY_CYCLE - 1; 			// Pulse width 1/3 of the period
	// TIMx control register 1
	// TIM4->CR1 = 1;					// Enable Timer

    /* Interrupts */
	TIM4->DIER |= (1 << 1);		        //enable UIE, interrupt enable -> falling edge
	// // TIM2->DIER |= 1;		            //enable UIE, interrupt enable -> interrupt from ccr1 val
    NVIC_EnableIRQ(TIM4_IRQn);
	/**************/
}



/**
 * @brief Init Timer 3 PWM, 16kHz, PA6
 * 
 * 
 */
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
	TIM3->PSC = TIM3_PRESCALER_VAL - 1;			// divided by 16000
	// TIMx auto-reload register
	TIM3->ARR = TIM3_ARR_REGISTER - 1; 			// divided by 26667
	// TIMx counter (TIMx_CNT)
	TIM3->CNT = 0;
	// TIMx capture/compare mode register 1
	TIM3->CCMR1 = 0x0060; 			// PWM mode
	// TIMx capture/compare enable register (TIMx_CCER)
	TIM3->CCER = 1;					// Enable PWM Ch1
	// TIMx capture/compare register 1
	TIM3->CCR1 = TIM2_DUTY_CYCLE - 1; 			// Pulse width 1/3 of the period
	// TIMx control register 1
	// TIM3->CR1 = 1;					// Enable Timer

    /* Interrupts */
	TIM3->DIER |= (1 << 1);		        //enable UIE, interrupt enable -> falling edge
	// // TIM2->DIER |= 1;		            //enable UIE, interrupt enable -> interrupt from ccr1 val
    NVIC_EnableIRQ(TIM3_IRQn);
	/**************/
}
//Clock 32 000 000
//PSC 	16 000
//Arr 	200
//32 000 000 / 16 000 = 2000
// 2000 / 200 = 20Hz
//CCr1 100/200 = 50%
//CCr1 150/200 = 75%

// 32 000 000 / 2 = 16 000 000
// 16 000 000 / 1000 = 16000


/**
 * @brief Init Timer 2 PWM, 16kHz, PA5
 * 
 * 
 */
void init_PWM_TIM2(void) {
	/* Basic PWM setup */
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
	TIM2->PSC = TIM2_PRESCALER_VAL - 1;				// divided by 16000
	// TIMx auto-reload register
	TIM2->ARR = TIM2_ARR_REGISTER - 1; 			// divided by 26667
	// TIMx counter (TIMx_CNT)
	TIM2->CNT = 0;
	// TIMx capture/compare mode register 1
	TIM2->CCMR1 = 0x0060; 			// PWM mode
	// TIMx capture/compare enable register (TIMx_CCER)
	TIM2->CCER = 1;					// Enable PWM Ch1
	// TIMx capture/compare register 1
	TIM2->CCR1 = TIM2_DUTY_CYCLE - 1; 			// Pulse width 1/3 of the period
	/*************************/

	/* Polarity */
	// Bit 1 CC1P: Capture/Compare 1 output Polarity
	// TIM2->CCER |= (1 << 1);
	/**************/

	/* Interrupts */
	TIM2->DIER |= (1 << 1);		        //enable UIE, interrupt enable -> falling edge
	// // TIM2->DIER |= 1;		            //enable UIE, interrupt enable -> interrupt from ccr1 val
    NVIC_EnableIRQ(TIM2_IRQn);
	/**************/
}

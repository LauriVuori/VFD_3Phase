/*This code tests NUCLEO-L152RE board transmitter UART communication by using
9600 BAUD and float print with sprintf
*/

/**
 * 14_4_2022
 * Sync between timers
 * Make real timer, new channel
 * setup interrupts all timers
 * 
 * 
 * 
 * 
 * 
 * 
 */

/**
 * Pin config
 * PA5 PWM TIM2
 * PA6 PWM TIM3
 * PB6 PWM TIM4
 * 
 * 
 */

/**
 * @file main.c
 * @author Lauri Vuori
 * @brief VDF driver
 * @version 0.1
 * @date 2022-01-26
 * 
 * 
 */



/* Includes */
#include "include.h"
#include "nucleo152start.h"
#include "table.h"
/* Private typedef */
/* Private define  */
/**
 * @brief pwm / timer configurations
 */
#define TIM2_PRESCALER_VAL 1 		// 32 mHz / 1 = 32mHz
#define TIM3_PRESCALER_VAL 1 		// 32 mHz / 1 = 32mHz
#define TIM4_PRESCALER_VAL 1 		// 32 mHz / 1 = 32mHz
#define TIM2_ARR_REGISTER 2000		// 32 mHz / 2000 = 16 000 Hz
#define TIM3_ARR_REGISTER 2000		// 32 mHz / 2000 = 16 000 Hz
#define TIM4_ARR_REGISTER 2000		// 32 mHz / 2000 = 16 000 Hz
#define TIM2_DUTY_CYCLE 1500
#define TIM3_DUTY_CYCLE 1500
#define TIM4_DUTY_CYCLE 1500
#define LAST_PWM_VAL 159
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

#define DEBUG_TIM2 1


void delay_Ms(int delay);

void init_PWM_TIM2(void);
void init_PWM_TIM3(void);
void init_PWM_TIM4(void);

void init_GPIO_PA8(void);
void set_GPIO_PA8(uint8_t set_bit);

/* Debug*/
void debug_APB1_TIM2_freeze(void);
void debug_APB1_TIM3_freeze(void);
void debug_APB1_TIM4_freeze(void);
void debug_APB1_TIM2_unfreeze(void);
void debug_APB1_TIM3_unfreeze(void);
void debug_APB1_TIM4_unfreeze(void);
/* Debug end*/

uint8_t tim2_counter = 0;
uint8_t tim3_counter = 0;
uint8_t tim4_counter = 0;
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/

// struct duty_cycles duty_cycles_values;
uint8_t ctr = 0;
int main(void) {
	/* Configure the system clock to 32 MHz and update SystemCoreClock */
	SetSysClock();
	SystemCoreClockUpdate();
	USART2_Init();
	init_PWM_TIM2();
	init_PWM_TIM3();
	init_PWM_TIM4();
	// init_GPIO_PA8();
	
	// debug_APB1_TIM2_unfreeze();
	debug_APB1_TIM2_freeze();
	debug_APB1_TIM3_freeze();

	TIM2->CR1 = 1;	
	TIM3->CR1 = 1;	
	TIM4->CR1 = 1;	
	while (1) {
		// TIM2->CCR1 += 10;
		// TIM3->CCR1 += 10;
		// // TIM4->CCR1 += 10;
		// if (TIM2->CCR1 > 2000) {
		// 	TIM2->CCR1 = 10;
		// 	// TIM4->CCR1 = 10;

		// }
		// if (TIM3->CCR1 > 2000) {
		// 	TIM3->CCR1 = 10;
		// 	USART2_write('d');
		// }
		// TIM2->CCR1 = table[ctr];
		// if (ctr == 159) {
		// 	ctr = 0;
		// }
		// ctr++;
		// delay_Ms(300);
	}
	return 0;
}

void test_table(void) {
	char buffer[15];
	uint16_to_char_array(table[159], buffer);
	USART2_write_string(buffer);
	USART2_write_string("\n\r");
	uint16_to_char_array(table[0], buffer);
	USART2_write_string(buffer);
	USART2_write_string("\n\r");

}

void set_GPIO_PA8(uint8_t set_bit) {
	if (set_bit == 0) {
		GPIOA->ODR &= ~((1 << 8));
	}
	else if (set_bit == 1) {
		GPIOA->ODR |= (1 << 8);
	}
}

/**
 * @brief Init GPIO PA8
 * 
 * 
 */
void init_GPIO_PA8(void) {
	RCC->AHBENR |= 1; 					// Enable PORT A clock, does not matter if its already on
	GPIOA->MODER &= ~((1 << 17) | (1 << 16));		// Clear bits 16,17
	GPIOA->MODER |= (1 << 16);			// bits 16. output 01.
}
/**
 * @brief TIM2 interrupt
 * 
 * 
 */

void TIM2_IRQHandler(void) {
	TIM2->SR=0;			                //clear UIF
	GPIOA->ODR ^= (1 << 8);

	TIM2->CCR1 = table[ctr];
	if (ctr == LAST_PWM_VAL) {
		ctr = 0;
		// change polarity
		TIM2->CCER ^= (1 << 1);
	}
	ctr++;

	// char buffer[15];
	// uint16_to_char_array(table[ctr], buffer);
	// USART2_write_string(buffer);
	// USART2_write_string("\n\r");
	// if (ctr == 159) {
	// 	ctr = 0;
	// }
	// ctr++;
}
/**
 * @brief Unfreeze TIM2 while debugging, timer will run while pause
 * 
 * 
 */
void debug_APB1_TIM2_unfreeze(void) {
	DBGMCU->APB1FZ &= ~1;
}
/**
 * @brief TIM2 will freeze durign debugging pause
 * 
 * 
 */
void debug_APB1_TIM2_freeze(void) {
	// Debug MCU APB1 freeze register
	DBGMCU->APB1FZ |= 1;
}

/**
 * @brief Unfreeze TIM3 while debugging, timer will run while pause
 * 
 * 
 */
void debug_APB1_TIM3_unfreeze(void) {
	DBGMCU->APB1FZ &= ~(1 << 1);
}
/**
 * @brief TIM3 will freeze durign debugging pause
 * 
 * 
 */
void debug_APB1_TIM3_freeze(void) {
	// Debug MCU APB1 freeze register
	DBGMCU->APB1FZ |= (1 << 1);
}

/**
 * @brief Unfreeze TIM4 while debugging, timer will run while pause
 * 
 * 
 */
void debug_APB1_TIM4_unfreeze(void) {
	DBGMCU->APB1FZ &= ~(2 << 1);
}
/**
 * @brief TIM4 will freeze durign debugging pause
 * 
 * 
 */
void debug_APB1_TIM4_freeze(void) {
	// Debug MCU APB1 freeze register
	DBGMCU->APB1FZ |= (2 << 1);
}



/**
 * @brief 
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
}

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

void delay_Ms(int delay)
{
	int i=0;
	for(; delay>0;delay--)
		for(i=0;i<2460;i++); //measured with oscilloscope
}

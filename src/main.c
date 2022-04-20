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
#include "timers.h"
#include "usart.h"
#include "gpio.h"
#include "debug.h"

/* Private typedef */
/* Private define  */

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

#define DEBUG_TIM2 1


void delay_Ms(int delay);



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

	// Start timers
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


/**
 * @brief TIM2 interrupt
 * 
 * 
 */

void TIM2_IRQHandler(void) {
	TIM2->SR=0;			                //clear UIF
	// GPIOA->ODR ^= (1 << 8);
	// set new duty value
	TIM2->CCR1 = table[tim2_counter];
	if (tim2_counter == LAST_PWM_VAL) {
		tim2_counter = 0;
		// change polarity
		TIM2->CCER ^= (1 << 1);
	}
	tim2_counter++;
}

void TIM3_IRQHandler(void) {
	TIM3->SR=0;			                //clear UIF
	// GPIOA->ODR ^= (1 << 8);
	// set new duty value
	TIM3->CCR1 = table[tim3_counter];
	if (tim3_counter == LAST_PWM_VAL) {
		tim3_counter = 0;
		// change polarity
		TIM3->CCER ^= (1 << 1);
	}
	tim3_counter++;
}

void TIM4_IRQHandler(void) {
	TIM4->SR=0;			                //clear UIF
	// GPIOA->ODR ^= (1 << 8);
	// set new duty value
	TIM4->CCR1 = table[tim4_counter];
	if (tim4_counter == LAST_PWM_VAL) {
		tim4_counter = 0;
		// change polarity
		TIM4->CCER ^= (1 << 1);
	}
	tim4_counter++;
}


void delay_Ms(int delay)
{
	int i=0;
	for(; delay>0;delay--)
		for(i=0;i<2460;i++); //measured with oscilloscope
}

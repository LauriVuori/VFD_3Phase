/**
 * 26_04_2022
 * Third phase
 * Make real timer, new channel, timer 9 works but needs adjusting
 * 
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
 * PA8 GPIO
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
#include "math.h"
#define PI 3.14159265358979323846
/* Private typedef */
/* Private define  */

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

#define DEBUG_TIM2 1
uint16_t test[160];

void delay_ms(uint16_t wait);

void calculate_phase1(void);

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

uint16_t time = 0;
int main(void) {
	/* Configure the system clock to 32 MHz and update SystemCoreClock */
	SetSysClock();
	SystemCoreClockUpdate();
	USART2_Init();
	init_PWM_TIM2();
	init_PWM_TIM3();
	init_PWM_TIM4();
	init_TIM9_upcounting();
	init_GPIO_PA8();
	
	// debug_APB1_TIM2_unfreeze();
	debug_APB1_TIM2_freeze();
	debug_APB1_TIM3_freeze();
	debug_APB1_TIM4_freeze();
	debug_APB2_TIM9_freeze();

	// Start timers
	TIM2->CR1 = 1;	
	TIM3->CR1 = 1;	
	TIM4->CR1 = 1;	
	TIM9->CR1 = 1;	
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
		// GPIOA->ODR ^= (1 << 8);
		// calculate_phase1();
	}
	return 0;
}
void calculate_phase1(void) {

    for (int i = 0; i < 160; i++) {
        test[i] = ((1000*sin(2*PI*i/320))+1000);
        // printf("%f %d\n", ((bits*sin(2*PI*i/320))+1000), t);
    }

}
void delay_ms(uint16_t wait) {
	wait *= 10;
	uint16_t difference = 0;
	uint16_t starttime = TIM9->CNT;
	while (difference <= wait) {
		difference = TIM9->CNT - starttime;
	}
}



void TIM9_IRQHandler(void) {
	TIM9->SR=0;			                //clear UIF
	// GPIOA->ODR ^= (1 << 8);
	time++;
	// set new duty value
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
	TIM2->CCR1 = phase1_table[tim2_counter];
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
	TIM3->CCR1 = phase2_table[tim3_counter];
	if (tim3_counter == LAST_PWM_VAL) {
		tim3_counter = 0;
		// change polarity
	}
	if (tim3_counter == 108) {
		TIM3->CCER ^= (1 << 1);
	}
	tim3_counter++;
}

void TIM4_IRQHandler(void) {
	TIM4->SR=0;			                //clear UIF
	// GPIOA->ODR ^= (1 << 8);
	// set new duty value
	TIM4->CCR1 = phase3_table[tim4_counter];
	if (tim4_counter == LAST_PWM_VAL) {
		tim4_counter = 0;
	}
	if (tim4_counter == 55) {
		TIM4->CCER ^= (1 << 1);
	}
	tim4_counter++;
}

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
void init_push_button(void);
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
void delay_Ms_osc(int delay);
/* Debug end*/

uint16_t tim2_counter = 0;
uint16_t tim3_counter = 0;
uint16_t tim4_counter = 0;
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/

uint8_t ramp_up_counter = 0; 
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
	
	//debug_APB1_TIM2_unfreeze();
	debug_APB1_TIM2_freeze();
	debug_APB1_TIM3_freeze();
	debug_APB1_TIM4_freeze();
	debug_APB2_TIM9_freeze();

	// Start timers
	TIM2->CR1 = 1;	
	TIM3->CR1 = 1;	
	TIM4->CR1 = 1;	
	TIM9->CR1 = 1;
	delay_Ms_osc(1000);	

	RCC->AHBENR|=0x4; //GPIOC enable. p154
	GPIOC->MODER&=~0xC000000; //PC13 configured to input, C=1100. p184
	while (1) {
		// debug Hz tables
		// if(~(GPIOC->IDR) & 0x2000){
		// 	delay_ms(500);
		// 	ramp_up_counter++;
		// 		if (ramp_up_counter == 9) {
		// 			while(1); // full speed 50hz
		// 		}
		// }

				// ramp up 5 hz per 1 sec
				ramp_up_counter++;
				delay_Ms_osc(1000);
				if (ramp_up_counter == 9) {
					while(1); // full speed 50hz
				}
	}
	return 0;
}

void init_push_button(void) {
	RCC->AHBENR|=0x4; //GPIOC enable. p154
	GPIOC->MODER&=~0xC000000; //PC13 configured to input, C=1100. p184
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
	if (ramp_up_counter == 0) {
		TIM2->CCR1 = phase1_table_5hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_5Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 1) {
		if (tim2_counter > LAST_PWM_VAL_10Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_10hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_10Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 2) {
		if (tim2_counter > LAST_PWM_VAL_15Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_15hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_15Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 3) {
		if (tim2_counter > LAST_PWM_VAL_20Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_20hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_20Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 4) {
		if (tim2_counter > LAST_PWM_VAL_25Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_25hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_25Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 5) {
		if (tim2_counter > LAST_PWM_VAL_30Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_30hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_30Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 6) {
		if (tim2_counter > LAST_PWM_VAL_35Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_35hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_35Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 7) {
		if (tim2_counter > LAST_PWM_VAL_40Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_40hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_40Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 8) {
		if (tim2_counter > LAST_PWM_VAL_45Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_45hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_45Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	if (ramp_up_counter == 9) {
		if (tim2_counter > LAST_PWM_VAL_50Hz) {
			tim2_counter = 0;
		}
		TIM2->CCR1 = phase1_table_50hz[tim2_counter];
		if (tim2_counter == LAST_PWM_VAL_50Hz) {
			tim2_counter = 0;
			// change polarity
			TIM2->CCER ^= (1 << 1);
		}
	}
	
	// TIM2->CCR1 = phase1_table_50hz[tim2_counter];
	// if (tim2_counter == LAST_PWM_VAL) {
	// 	tim2_counter = 0;
	// 	// change polarity
	// 	TIM2->CCER ^= (1 << 1);
	// }
	tim2_counter++;
}

void TIM3_IRQHandler(void) {
	TIM3->SR=0;			                //clear UIF
	// GPIOA->ODR ^= (1 << 8);
	// set new duty value
	TIM3->CCR1 = phase2_table[tim3_counter];
	if (tim3_counter == LAST_PWM_VAL_50Hz) {
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
	if (tim4_counter == LAST_PWM_VAL_50Hz) {
		tim4_counter = 0;
	}
	if (tim4_counter == 55) {
		TIM4->CCER ^= (1 << 1);
	}
	tim4_counter++;
}


void delay_Ms_osc(int delay)
{
	int i=0;
	for(; delay>0;delay--)
		for(i=0;i<2460;i++); //measured with oscilloscope
}
#include "gpio.h"

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
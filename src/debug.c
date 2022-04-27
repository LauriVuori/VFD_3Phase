#include "debug.h"

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
 * @brief Unfreeze TIM4 while debugging, timer will run while pause
 * 
 * 
 */
void debug_APB2_TIM9_unfreeze(void) {
	DBGMCU->APB2FZ &= ~(2 << 1);
}
/**
 * @brief TIM4 will freeze durign debugging pause
 * 
 * 
 */
void debug_APB2_TIM9_freeze(void) {
	// Debug MCU APB1 freeze register
	DBGMCU->APB2FZ |= (2 << 1);
}
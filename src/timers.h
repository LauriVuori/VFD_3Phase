#include "include.h"
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


void init_PWM_TIM2(void);
void init_PWM_TIM3(void);
void init_PWM_TIM4(void);
void init_TIM9_upcounting(void);
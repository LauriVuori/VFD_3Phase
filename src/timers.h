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
#define LAST_PWM_VAL_50Hz 159
#define LAST_PWM_VAL_45Hz 176
#define LAST_PWM_VAL_40Hz 199
#define LAST_PWM_VAL_35Hz 227
#define LAST_PWM_VAL_30Hz 266
#define LAST_PWM_VAL_25Hz 319
#define LAST_PWM_VAL_20Hz 399
#define LAST_PWM_VAL_15Hz 532
#define LAST_PWM_VAL_10Hz 799
#define LAST_PWM_VAL_5Hz 1599

#define PHASE2_POLARITY_50HZ 108
#define PHASE2_POLARITY_45HZ 119
#define PHASE2_POLARITY_40HZ 134
#define PHASE2_POLARITY_35HZ 153
#define PHASE2_POLARITY_30HZ 179
#define PHASE2_POLARITY_25HZ 214
#define PHASE2_POLARITY_20HZ 268
#define PHASE2_POLARITY_15HZ 356
#define PHASE2_POLARITY_10HZ 534
#define PHASE2_POLARITY_5HZ 1056

#define PHASE3_POLARITY_50HZ 54
#define PHASE3_POLARITY_45HZ 60
#define PHASE3_POLARITY_40HZ 68
#define PHASE3_POLARITY_35HZ 77
#define PHASE3_POLARITY_30HZ 90
#define PHASE3_POLARITY_25HZ 108
#define PHASE3_POLARITY_20HZ 134
#define PHASE3_POLARITY_15HZ 179
#define PHASE3_POLARITY_10HZ 268
#define PHASE3_POLARITY_5HZ 534

void init_PWM_TIM2(void);
void init_PWM_TIM3(void);
void init_PWM_TIM4(void);
void init_TIM9_upcounting(void);
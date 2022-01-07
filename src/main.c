/*This code tests NUCLEO-L152RE board transmitter UART communication by using
9600 BAUD and float print with sprintf
*/

/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"
#include "nucleo152start.h"
#include <stdio.h>
#include <stdlib.h>

/* Private typedef */
/* Private define  */
/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void USART2_Init(void);
void USART2_write(char data);
void delay_Ms(int delay);
void init_pwm1(void);

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
	/* TODO - Add your application code here */
	char buf[100];
	init_pwm1();


	/* Infinite loop */
	while (1) {
		TIM2->CCR2 += 100;
		delay_Ms(500);
	}
	return 0;
}

void USART2_Init(void) {
	RCC->APB1ENR|=0x00020000; 	//set bit 17 (USART2 EN)
	RCC->AHBENR|=0x00000001; 	//enable GPIOA port clock bit 0 (GPIOA EN)
	GPIOA->AFR[0]=0x00000700;	//GPIOx_AFRL p.188,AF7 p.177
	GPIOA->AFR[0]|=0x00007000;	//GPIOx_AFRL p.188,AF7 p.177
	GPIOA->MODER|=0x00000020; 	//MODER2=PA2(TX) to mode 10=alternate function mode. p184
	GPIOA->MODER|=0x00000080; 	//MODER2=PA3(RX) to mode 10=alternate function mode. p184

	USART2->BRR = 0x00000D05;	//9600 BAUD and crystal 32MHz. p710, D05
	USART2->CR1 = 0x00000008;	//TE bit. p739-740. Enable transmit
	USART2->CR1 |= 0x00000004;	//RE bit. p739-740. Enable receiver
	USART2->CR1 |= 0x00002000;	//UE bit. p739-740. Uart enable
}

// 17.3.9 PWM mode
// p.404

// Pulse width modulation mode allows generating 
// a signal with a frequency determined by the 
// value of the TIMx_ARR register and a duty cycle 
// determined by the value of the 
// TIMx_CCRx register

//https://deepbluembedded.com/stm32-pwm-example-timer-pwm-mode-tutorial/
// TIMx_ARR auto reload register p435
// TIMx_PSC prescaler
//https://github.com/fcayci/stm32f1-bare-metal
void init_pwm1(void) {
	RCC->AHBENR |= 1; 			//GPIOA ABH bus clock ON. p154
	GPIOA->MODER &= ~0x0000000C;	//clear (input reset state for PA1). p184
	GPIOA->MODER |= 0x00000008; 	//GPIOA pin 1 (PA1) to alternate function. p184
	GPIOA->AFR[0] &= ~0x000000F0;	//clear AFRL1 bits. p188

	//TIM2_CH2 connected to PA1, STM32L152RET6 datasheet p47.
	GPIOA->AFR[0] |= 0x00000010; 	//AF1 (TIM2) GPIOA pin 1 (PA1). p177, p188

	//Timers table can be found form STM32L152RET6 datasheet p28.
	//Functional overwiev STM32L152RET6 datasheet p13

	//Timer block diagram p384
	RCC->APB1ENR|=1; 			//TIM2EN: Timer 2 clock enable. p160
	TIM2->PSC=32-1; 			//TIMx prescaler: 32 000 000 MHz / 32 000 = 1 000 Hz. p435
	TIM2->ARR=1000-1; 			//TIMx auto-reload register. 1 000 Hz / 10000 = 0,1 Hz ~ 10s. p435

	//CCMR1=TIMx capture/compare mode register 1, Bits 14:12 OC2M[2:0]: Output compare 2 mode
	TIM2->CCMR1=0x3000;			//011: Toggle - OC2REF toggles when TIMx_CNT=TIMx_CCR2. p430
	TIM2->CCR2=0;				//TIM2 capture/compare register 2. p435

	//OC2 signal is output on the corresponding output pin. p434
	TIM2->CCER|=0x10;			//Bit 4 CC2E: Capture/Compare 1 output enable. p434
	TIM2->CNT=0;				//counter start value = 0
	TIM2->CR1=1; 				//TIMx control register 1, TIM2 Counter enabled. p421

	// TIM2->ARR = 0;
	// TIM2->PSC = 0;
}
void USART2_write(char data) {
	//wait while TX buffer is empty
	while(!(USART2->SR & 0x0080)){} 	//6. p736-737
		USART2->DR = (data);		//p739
}

void delay_Ms(int delay) {
	int i=0;
	for(;delay>0;delay--)
		for(i=0;i<2460;i++); //measured with oscilloscope
}

#include "usart.h"
void USART2_Init(void)
{
	RCC->APB1ENR |= 0x00020000;	 // set bit 17 (USART2 EN)
	RCC->AHBENR |= 0x00000001;	 // enable GPIOA port clock bit 0 (GPIOA EN)
	GPIOA->AFR[0] = 0x00000700;	 // GPIOx_AFRL p.188,AF7 p.177
	GPIOA->AFR[0] |= 0x00007000; // GPIOx_AFRL p.188,AF7 p.177
	GPIOA->MODER |= 0x00000020;	 // MODER2=PA2(TX) to mode 10=alternate function mode. p184
	GPIOA->MODER |= 0x00000080;	 // MODER2=PA3(RX) to mode 10=alternate function mode. p184

	USART2->BRR = 0x00000D05;  // 9600 BAUD and crystal 32MHz. p710, D05
	USART2->CR1 = 0x00000008;  // TE bit. p739-740. Enable transmit
	USART2->CR1 |= 0x00000004; // RE bit. p739-740. Enable receiver
	USART2->CR1 |= 0x00002000; // UE bit. p739-740. Uart enable
}

void USART2_write(char data)
{
	// wait while TX buffer is empty
	while (!(USART2->SR & 0x0080))
	{
	}					 // 6. p736-737
	USART2->DR = (data); // p739
}
void USART2_write_string(char data[])
{
	for (int i = 0; data[i] != '\0'; i++)
	{
		// wait while TX buffer is empty
		while (!(USART2->SR & 0x0080))
		{
		} // USART register map and reset values, TXe bit 7
		USART2->DR = (data[i]);
	}
}

void uint8_to_char_array(uint8_t uInteger, uint8_t * dest_array) {
    // needs atleast [6] array
	uint8_t* ptr_to_buffer;
	uint8_t int_buffer [5];

	ptr_to_buffer = &int_buffer[4];        // Point to buffer end
    *ptr_to_buffer = 0;
	do {
        // make characters, (uInteger % 10) = 5, 5 + '0' = 53=='5'
        *--ptr_to_buffer = (uInteger % 10) + '0';
    }while (uInteger /= 10 );
	while (*ptr_to_buffer) {
        *dest_array = *ptr_to_buffer;
        dest_array++;
        ptr_to_buffer++;
	}
    // end char
    *dest_array = '\0';
}


void uint16_to_char_array(uint16_t uInteger, uint8_t * dest_array) {
	// needs atleast [6] array
	uint8_t* ptr_to_buffer;
	uint8_t int_buffer [11];

	ptr_to_buffer = &int_buffer[10];        // Point to buffer end
	*ptr_to_buffer = 0;
	do {
		// make characters, (uInteger % 10) = 5, 5 + '0' = 53=='5'
		*--ptr_to_buffer = (uInteger % 10) + '0';
	}while (uInteger /= 10 );

	while (*ptr_to_buffer) {
		*dest_array = *ptr_to_buffer;
		dest_array++;
		ptr_to_buffer++;
	}
	// end char
	*dest_array = '\0';
}

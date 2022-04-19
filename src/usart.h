#include "include.h"
void USART2_Init(void);
void USART2_write(char data);
void USART2_write_string(char data[]);
void uint8_to_char_array(uint8_t uInteger, uint8_t * dest_array);
void uint16_to_char_array(uint16_t uInteger, uint8_t * dest_array);

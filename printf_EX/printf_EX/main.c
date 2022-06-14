/*
 * printf_EX.c
 *
 * Created: 2022-06-07 오후 2:35:24
 * Author : user
 */ 

#include <avr/io.h>
#include "usart_printf.h"
#include <util/delay.h>


int main(void)
{
    USART_Init();								// USART 초기화
	stdout = &device;							// 표준 입력장치 설정
	
    while (1) 
    {
		printf("Hello ATmega128\n");			// 그냥 이렇게 쓰면 됨
		_delay_ms(1000);
    }
	return 0;
}


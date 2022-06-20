/*
 * ex_printf_usart.c
 *
 * Created: 2022-06-07 오후 2:19:49
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "usart_printf.h"


int main(void)
{
	USART_Init();		// usart 초기화
	stdout = &device;	// 표준출력으로 사용할 장비 설정
	
    while (1) 
    {
		printf("Hello ATmega123\n");
		_delay_ms(1000);
    }
	return 0;
}


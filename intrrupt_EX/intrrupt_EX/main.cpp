/*
 * intrrupt_EX.cpp
 *
 * Created: 2022-05-17 오후 2:34:27
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PORT PORTB
#define LED_DDR DDRB

int led_flag = 0;				// 어떠한 상태의 기준을 정하기 위해 사용

void init_EINT(){							// 인터럽트 세부사항 초기화 (ISC40 같은것)
	EICRB |= ((1<<ISC41) | (0<<ISC40));   // 인터럽트가 일어나는 기준 (4가지있는 그거) ( << 앞의 숫자가 기준)
	EIMSK |= (1<<INT4);						// 인터럽트 허용
}
void init_EINT1(){
	EICRB |= ((1<<ISC51) | (0<<ISC50));   // 인터럽트가 일어나는 기준 (4가지있는 그거) ( << 앞의 숫자가 기준)
	EIMSK |= (1<<INT5);						// 인터럽트 허용
}

/*ISR(INT4_vect){    // 과제 1
	if(led_flag)
	{
		led_flag =0;
		LED_PORT = 0x00;
	}
	else
	{
		led_flag =1;
		LED_PORT = 0xff;
	}
	
}*/

ISR(INT4_vect){    // INT4애서 인터럽트가 발생할 경우 자동으로 실행
	LED_PORT = 0xff;

}

ISR(INT5_vect){
	LED_PORT = 0x00;

}

int main(void)
{
	LED_DDR = 0xff;
	LED_PORT = 0x00;
	
	init_EINT();
	init_EINT1();
	sei();				// 전체 인터럽트를 활성화 
	
    while (1) 
    {
		;
    }
	return 0;
}


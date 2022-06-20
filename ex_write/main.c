/*
 * ex_write.c
 *
 * Created: 2022-06-07 오후 2:43:49
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart_printf.h"

#define LED_PORT PORTB
#define LED_DDR DDRB

const int sensor_Flag = 1025;

/* ADC 초기화 함수 구현 */
void Init_ADC()
{
	// ADC1 채널, AREF 기준 전압 및 채널을 선택
	  ADMUX  = (1<<REFS0) | (1<<MUX0); 
	// 채널, 활성화, 프리스케일 설정
	 ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);    
}

/* ==ADC 변환 함수 구현 */
unsigned int CDS_StartADCConverter()
{
	unsigned int result;
	
	cli();									// ADC 변환중 인터럽트 금지
	
	ADCSRA |= (1<<ADSC);					// ADC 변환 시작
	while(!(ADCSRA & (1<<ADIF)));			// ADC 변환 완료 신호 대기
	
	result = ADCL;							// 변환 결과 저장
	result |= ((ADCH & 0x03)<<8);	
	
	sei();									// 인터럽트 허용
	
	return result;
}

int main(void)
{
	LED_DDR = 0xff;
	
    USART_Init();
    stdout = &device;
	
	unsigned int AdcResult;							// 변환값 저장 변수
	
	Init_ADC();										// ADC 초기화
	
	while (1) 
    {	
		AdcResult = CDS_StartADCConverter();		// ADC 변환 실행
		if(AdcResult >= sensor_Flag){
			LED_PORT = 0x00;
		}else{
			LED_PORT = 0xff;
		}
    }
	return 0;
}


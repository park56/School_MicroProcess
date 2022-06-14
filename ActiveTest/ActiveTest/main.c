/*
 * ActiveTest.c
 *
 * Created: 2022-06-14 오후 1:21:14
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "usart_printf.h"
#include "tlcd.h"

#define LED_P PORTE
#define LED_D DDRE

#define FND_P PORTB
#define FND_D DDRB

#define SW_P PINC
#define SW_D DDRC

#define BUZZ_P PORTD
#define BUZZ_D DDRD 

#define BAUD_RATE 51

#define FLAG_VALUE 150

volatile unsigned char rxData;

int n;

void Init_ADC()
{
	//- ADC1 채널, AREF 기준 전압 => AVCC로 H/W 설정
	ADMUX  = (1<<REFS0) | (1<<MUX0) | (1<<n);
	
	//- 채널, 활성화, 프리스케일 설정
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

unsigned int startADConverter()
{
	unsigned int result;

	cli();									//- ADC 변환 중 인터럽트 금지

	ADCSRA |= (1<<ADSC);					//- ADC 변환 시작
	while(!(ADCSRA & (1<<ADIF))) ;			//- ADC 변환 완료 신호 대기

	result = ADCL;		            	 	//- 변환 결과 저장
	result |= ((ADCH & 0x03) << 8);

	sei();									//- 인터럽트 허용

	return result;
}

// test1
void test1(){
	
	int FND_NUM[8] = {0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F};
	int realnum[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
	
	while(1){
		
		for(int i = 0;i <8; i++){
			
			if(realnum[i] == SW_P){		// 0,1,2,3,4,5
				FND_P = FND_NUM[i];
				
				LED_P = 0x01;
				for(int j = 0; j< i; j++){
					LED_P = LED_P << 1;
					LED_P += 1;
				}
			}
		}
	}
}

// test2
/*void test2(){
	unsigned int AdcResult;							//- 변환값 저장 변수

	USART_Init();		                            //- USART1 초기화
	stdout = &device;	                            //- 표준출력으로 사용할 장치 설정

	Init_ADC();										//- ADC 초기화

	
	while(1)
	{
		AdcResult = startADConverter();				//- ADC 변환 실행
		if(AdcResult > FLAG_VALUE){
			LED_P = 0x00;
		}else{
			LED_P = 0xff;
		}
	}
}*/

// test3
/*char command[3] = {0};
int cnt = 0;

ISR(USART1_RX_vect){
	
	if(UCSR1A & (1<<RXC1)){
		rxData = UDR1;
		
		if(rxData != '\n'){
			command[cnt++] = rxData;
		}else{
			if(command[0] == 'L'){
				
				if(command[2] == '1'){
					LED_P = LED_P |(0x01 << (command[1]-'0'));
				}else{
					LED_P -= (0x01 << (command[1]-'0'));
				}
				
			}else if(command[0] == 'B'){
				
				if(command[1] == '1'){
					BUZZ_P = 0x00;
					}else{
					BUZZ_P = 0xff;
				}
			}
			cnt = 0;
		}
	}
}*/

// test4
/*ISR(USART1_RX_vect){
	
	//SendCommand(CMD_CLEAR_DISPLAY);
	
	if(UCSR1A & (1<<RXC1)){
		rxData = UDR1;									
		
		if(rxData == 'T'){
			n = 1;
			Init_ADC();
			int AdcResult = startADConverter();
			char str[20];
			sprintf(str,"T:%d",AdcResult);
			SendText(DDRAM_ADDR | 0x00, str);
			
		}else if(rxData == 'L'){
			n = 0;
			Init_ADC();
			int AdcResult = startADConverter();
			char str[20];
			sprintf(str,"L:%d",AdcResult);
			SendText(DDRAM_ADDR | 0x00, str);
			
		}
	}
}*/
	
int main(void)
{
	n=0;
	LED_D = 0xff;
	FND_D = 0xff;
	BUZZ_D = 0xff;
	SW_D = 0x00;
	
	LED_P = 0x00;
	FND_P = 0x00;
	BUZZ_P = 0xff;
	
	sei();
	USART_Init();
	
	Init_ADC();

	TXT_LCD_Init();
	
	test1();
	//test2();
	//while(1){;}
}


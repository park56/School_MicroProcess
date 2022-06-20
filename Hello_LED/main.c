/*
* Hello_LED.c
*
* Created: 2022-03-29 오후 2:04:22
* Author : DGSW
*/

#include <avr/io.h>
#include <util/delay.h>

// Sensor PIN 설정
#define LED_DDR DDRE    // 입출력 모드 설정 레지스터
#define LED_PORT PORTE  // 출력 데이터 저장 레지스터


void PART1()
{
	LED_DDR = 0xff;
	LED_PORT = 0xff;
	
	for(int i =0;i<10;i++){
		LED_PORT = 0xff;
		_delay_ms(500);
		
		// LED OFF
		LED_PORT = 0x00;
		_delay_ms(500);
	}
}

void PART2(){
	
	LED_PORT = 0xff;
	int EX_PORT = 0xff;
	for(int i = 0; i<8; i++){
		EX_PORT <<= 1;
		LED_PORT = 0xff ^ EX_PORT;
		_delay_ms(300);
	}
	EX_PORT = 0x00;
	for(int i = 0; i<8; i++){
		LED_PORT >>= 1;
		_delay_ms(300);
	}
}

void PART3() {
	LED_PORT = 0x01;
	DDRF = 0x00; 
	
	for(int i=1; i<8; i++){
		LED_PORT <<= 1;
		DDRF = 0x01;
		if(i %2 !=0){   // 부저 울림
			DDRF = 0x00;
			_delay_ms(1500);
		}else{
			DDRF = 0x01;
			_delay_ms(1500);
		}
		}	
		DDRF = 0x00;
		LED_PORT = 0x00;
}

// 엔트로 포인트 함수
int main(void)
{
	LED_DDR = 0xff;
	LED_PORT = 0x01;
	
	//PART1();
	//PART2();
	PART3();
}


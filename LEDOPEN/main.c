/*
 * LEDOPEN.c
 *
 * Created: 2022-03-29 오후 3:35:24
 * Author : DGSW
 */ 

#include <avr/io.h>
#include <util/delay.h>

#define LED_DDR DDRE    // 입출력 모드 설정 레지스터
#define LED_PORT PORTE  // 출력 데이터 저장 레지스터

int main(void)
{
 LED_DDR = 0x01;
 LED_PORT = 0x01;
 
 for(int i =0;i<8;i++){
		LED_PORT = 0x01;
		_delay_ms(3000);
		
		// LED OFF
		LED_PORT = 0x00;
		_delay_ms(3000);
 }
 
}


/*
 * tcld.c
 *
 * Created: 2022-05-31 오후 2:22:44
 * Author : user
 */ 

#include <avr/io.h>
#include "tlcd.h"
#include <util/delay.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#define LED_P PORTB

#define BAUD_RATE 51

int endCount = 0;

unsigned char rxData;

void USART_Init(){

	UBRR1H = (unsigned char) BAUD_RATE >> 8;
	UBRR1L = (unsigned char) BAUD_RATE;

	//UCSR1B = (1<<TXEN1);
	UCSR1B = (1<<RXCIE1) | (1<<TXEN1) | (1<<RXEN1);			 // 수신, 송신, 수신인터럽트 기능 설정
	UCSR1C = (1<<UCSZ11) | (1<<UCSZ10);						// no parity, 1 stop bit, 8 bit data
}

void USART_Transmitter(unsigned char txData){

	while(!(UCSR1A & (1<<UDRE1)));		// 송신 버퍼가 빌때까지 대기
	UDR1 = txData;					// 버퍼에 데이터 채우기
}

ISR(USART1_RX_vect){
	
	// 수신 버퍼에서 읽어 온 데이터를 다시 송신
	if(UCSR1A & (1<<RXC1)){
		rxData = UDR1;							// 수신버퍼 데이터를 변수에 저장
		USART_Transmitter(rxData);				// rxData를PC로 전송
		
		if(rxData != '\n') {
			SendData(rxData);
			endCount++;
			if(endCount == 16){
				SendCommand(DDRAM_ADDR|0x40);
			}
			if(endCount == 32){
				SendCommand(CMD_CLEAR_DISPLAY);
				endCount = 0;
			}
		}
	}
}

/*qISR(USART1_RX_vect){
	
	// 수신 버퍼에서 읽어 온 데이터를 다시 송신
	if(UCSR1A & (1<<RXC1)){
		rxData = UDR1;							// 수신버퍼 데이터를 변수에 저장
		USART_Transmitter(rxData);				// rxData를PC로 전송
	}
}*/


int main(void)
{
	//SendText(DDRAM_ADDR | 0x00, "HELLO WORLD");			// 1행에 문자출력
	//SendText(DDRAM_ADDR | 0x40, "123456789");		// 2행에 문자 출력
	
	TXT_LCD_Init();				// LCD 제어 설정 및 초기화
	
	LED_P = 0x00;
	DDRB = 0xff;
	
	USART_Init();	
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		;
    }
	return 0;
}


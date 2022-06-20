/*
 * ex_usart_rtx.c
 *
 * Created: 2022-05-24 오후 2:57:47
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>  // rx 수신 처리 인터럽트

#define BAUD_RATE 51

volatile unsigned char rxData;			// 송수신 데이터 저장 변수

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
	}
}

int main(void)
{
	USART_Init();
	
	sei();
	
	USART_Transmitter('S');

    while (1)
    {
	   ;
    }
	return 0;
}


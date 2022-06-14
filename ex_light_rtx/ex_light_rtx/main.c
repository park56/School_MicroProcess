/*
 * ex_light_rtx.c
 *
 * Created: 2022-05-24 오후 3:48:11
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define LED_P PORTB

#define BAUD_RATE 51

volatile unsigned char rxData;	

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
	}
	
	if(rxData == '1'){	
		if(LED_P == 1){
			rxData = '0';
		}
	}
	
	LED_P = 0x00;
	for(int i = 0; i < rxData-'0'; i++){
		LED_P = LED_P << 1;
		LED_P |= 1;
	}
}

int main(void)
{
	LED_P = 0x00;
	DDRB = 0xff;
	
	USART_Init();
	
	sei();
	
	while (1)
	{
		;
	}
	return 0;
}


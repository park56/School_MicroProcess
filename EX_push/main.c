/*
 * EX_push.c
 *
 * Created: 2022-04-05 오후 2:02:40
 * Author : DGSW
 */ 

#include <avr/io.h>

#define LED_DDR DDRE
#define LED_PORT PORTE

#define SwitchDDR DDRC
#define SwitchPIN PINC

#define BuzzS DDRF

void one(){
	while(1){
		LED_PORT = ~SwitchPIN;
	}
}

void two(){
	
	while(1){
		if(SwitchPIN == 0xfe){
			BuzzS = 0x01;
		}
		if(SwitchPIN == 0xfd){
			BuzzS = 0x00;
		}
	}
}


int main(void)
{	
	SwitchDDR = 0x00;
	LED_DDR = 0xff;
	BuzzS = 0x00;
	
	//one();
	two();
}


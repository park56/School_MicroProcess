/*
* segment.c
*
* Created: 2022-04-12 오후 1:50:12
* Author : DGSW
*/
#include <avr/io.h>
#include <util/delay.h>

#define segddr DDRB
#define segpin PORTB

#define SwitchDDR DDRC
#define SwitchPIN PINC

void study1(){
	while (1)
	{
		segpin = 0x00;
		_delay_ms(500);
		segpin = 0xff;
		_delay_ms(500);
	}
}

void study2(){
	int num[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	int eng[6]={0x77,0x7f,0x39,0x3f,0x79,0x71};
	for(int i = 0; i<10;i++){
		segpin = num[i];
		_delay_ms(1000);
	}
	for(int i = 0; i<6;i++){
		segpin = eng[i];
		_delay_ms(1000);
	}
}

void study3(){
		DDRC = 0x00;
		segddr = 0xff;
		segpin = 0x00;
		
		//int realnum[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40};
		int realnum[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
		int num[9] = {0x3f,0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F};
		
		while(1){
			for(int i = 0;i <8; i++){
				if(realnum[i] == SwitchPIN){   //	if(realnum[i] == ~SwitchPIN)
					segpin = num[i];
					_delay_ms(500);
				}
			}
		}
}

int main(void)
{
	//study1();
	//study2();
	study3();
}


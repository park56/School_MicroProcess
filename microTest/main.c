/*
 * microTest.c
 *
 * Created: 2022-04-19 오후 1:33:28
 * Author : DGSW
 */ 

#include <avr/io.h>
#include <util/delay.h>

// 세그먼트 선언
#define segddr DDRB
#define segport PORTB

// 스위치 선언
#define switchddr DDRC
#define switchpin PINC

// LED 선언
#define ledddr DDRE
#define ledport PORTE

// 필요 배열
int realnum[8] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
int num[9]={0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int eng[6]={0x77,0x7f,0x39,0x3f,0x79,0x71};
	
int numeng[6] = {0x06,0x4f,0x6d,0x07,0x77,0x71};
int lednum[6] = {0x01, 0x07, 0x1f, 0x7f, 0xff, 0x00};

void test1(){
while(1){
	if((switchpin^0xff) == 0x01){
		for(int i = 0; i<9; i++){
			segport=num[i];
			if((switchpin^0xff) == 0x10){
				segport = 0x00;
				break;
			}
			_delay_ms(1000);
		}
	}
	
	if((switchpin^0xff) == 0x02){
		for(int i = 0; i<8; i++){
			i++;
			segport=num[i];
			if((switchpin^0xff) == 0x10){
				segport = 0x00;
				break;
			}
			_delay_ms(1000);
		}
	}
	
	if((switchpin^0xff) == 0x04){
		for(int i = 0; i<8; i++){
			i+=2;
			segport=num[i];
			if((switchpin^0xff) == 0x10){
				segport = 0x00;
				break;
			}
			_delay_ms(1000);
		}
	}
	
	if((switchpin^0xff) == 0x08){
		for(int i = 0; i<6; i++){
			segport=eng[i];
			if((switchpin^0xff) == 0x10){
				segport = 0x00;
				break;
			}
			_delay_ms(1000);
		}
	}
	
	if((switchpin^0xff) == 0x10){
		segport = 0x00;
	}
}
}
	
void test2(){
		for(int i = 0; i<8; i++){
			ledport <<= 1;
			ledport += 0x01;
			
			if(i == 7){
				DDRF = 0xff;
				_delay_ms(1000);
				DDRF = 0x00;
			}
			_delay_ms(1000);
		}

		for(int i = 0; i<8; i++){
			ledport >>= 1;
			
			if(i == 7){
				DDRF = 0xff;
				_delay_ms(1000);
				DDRF = 0x00;
			}
			_delay_ms(1000);
		}
}

void test3(){
	for(int i=0; i<3; i++){
		for(int i =0;i <6; i++){
			segport = numeng[i];
			ledport = lednum[i];
			_delay_ms(1000);
		}
	}
}

int main(void)
{
	// 초기설정
	segddr = 0xff;
	ledddr = 0xff;
	switchddr = 0x00;

	test1();
	//test2();
	//test3();	
}


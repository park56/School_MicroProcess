/*
 * EX_TEST.cpp
 *
 * Created: 2022-05-10 오후 3:31:31
 * Author : user
 */ 

#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
    /* Replace with your application code */
    DDRE = 0xff;
	PORTE = 0x01;
	while (1) 
    {
		/*for(int i =0 ;i<8; i++){
			_delay_ms(500);
			PORTE = PORTE >> 1;
		}*/
		PORTE = 0x00;
		}
}


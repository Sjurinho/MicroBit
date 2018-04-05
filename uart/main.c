#include "uart.h"
#include "gpio.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}


int main(){
	uart_init();
	//configure buttons
	GPIO->PIN_CNF[17] = 0;
	GPIO->PIN_CNF[26] = 0;
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}


	int sleep = 0;
	iprintf("Norway has %d counties.\n\r", 18);

	while(1){
		if(!(GPIO->IN & (1 << 26))){
			uart_send('B');
		}
		if(!(GPIO->IN & (1 << 17))){
			uart_send('A');
		}
		char letter = uart_read();
		if(letter != '\0'){
			if(!(GPIO->IN & (1<<14))){
				for (int i = 13; i < 16; ++i){
				GPIO->OUTSET = (1<<i);
				}
			}
			else{
				for (int i = 13; i < 16; ++i){
					GPIO->OUTCLR = (1<<i);
				} 
			}
			sleep = 100000;
			while(--sleep);
		}

	}
	return 0;
	//sudo picocom -b 9600 /dev/ttyACM0
}
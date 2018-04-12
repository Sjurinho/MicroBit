#include <stdint.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"


int main(){
	// Configure LED Matrix
	for(int i = 4; i <= 12; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure tasks and events
	GPIOTE->CONFIG[0] = 0x00021101;
	GPIOTE->CONFIG[1] = 0x00130D03;
	GPIOTE->CONFIG[2] = 0x00130E03;
	GPIOTE->CONFIG[3] = 0x00130F03;

	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);
	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);
	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);
	PPI->CHENSET = 0x7;

	
	while(1){
		/*if(!(GPIO->IN & (1 << 17))){
			GPIOTE->CONFIG[1] = GPIOTE->CONFIG[1] ^ 0x00100000;
			GPIOTE->CONFIG[2] = GPIOTE->CONFIG[2] ^ 0x00100000;
			GPIOTE->CONFIG[3] = GPIOTE->CONFIG[3] ^ 0x00100000;
		}*/
		int sleep = 100000;
		while(--sleep);

	}

	return 0;
}

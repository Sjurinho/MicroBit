#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"
#define UART ((NRF_UART_REG*)0x40002000)

//TGT_RXD: #P.025
//TGT_TXD: #P.024
typedef struct {
	/*tasks*/
	volatile uint32_t STARTRX;
	volatile uint32_t STOPRX;
	volatile uint32_t STARTTX;
	volatile uint32_t STOPTX;
	volatile uint32_t RES0[3];
	volatile uint32_t SUSPEND;

	volatile uint32_t RES1[56];
	/*events*/
	volatile uint32_t CTS;
	volatile uint32_t NCTS;
	volatile uint32_t RXDRDY;
	volatile uint32_t RES2[4];
	volatile uint32_t TXDRDY;
	volatile uint32_t RES3[1];
	volatile uint32_t ERROR;
	volatile uint32_t RES4[7];
	volatile uint32_t RXTO;
	
	volatile uint32_t RES5[110];
	/*registers*/
	volatile uint32_t INTEN;
	volatile uint32_t INTENSET;
	volatile uint32_t INTENCLR;
	volatile uint32_t RES6[93];
	volatile uint32_t ERRORSRC;
	volatile uint32_t RES7[31];
	volatile uint32_t ENABLE;
	volatile uint32_t RES8[1];
	volatile uint32_t PSELRTS;
	volatile uint32_t PSELTXD;
	volatile uint32_t PSELCTS;
	volatile uint32_t PSELRXD;
	volatile uint32_t RXD;
	volatile uint32_t TXD;
	volatile uint32_t RES9[1];
	volatile uint32_t BAUDRATE;
	volatile uint32_t RES10[17];
	volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init(){
//RXD og CTS skal i input. Output value not applicable
//RTS og TXD skal i output. Output value 1.
	GPIO->PIN_CNF[24] = 1;
	GPIO->PIN_CNF[25] = 0;
	/*configure which pins to be used by UART*/
	UART->PSELTXD = 24;
	UART->PSELRXD = 25;
	/*disable CTS and RTS*/
	UART->PSELCTS = 0xFFFFFFFF;
	UART->PSELRTS = 0xFFFFFFFF;
	/*set baudrate*/
	UART->BAUDRATE = 0x00275000;
	/*enable UART*/
	UART->ENABLE = 4;
	UART->STARTRX = 1;
}

void uart_send(char letter){
	UART->STARTTX = 1;
	UART->TXDRDY = 0;
	UART->TXD = letter;
	while(!(UART->TXDRDY));
	UART->STOPTX = 1;
}

char uart_read(){
	if (!(UART->RXDRDY)){
		return '\0';
	}
	UART->STARTRX = 1;
	UART->RXDRDY = 0;
	char letter = UART->RXD;
	//while(!(UART->RXDRDY));
	return letter;
}

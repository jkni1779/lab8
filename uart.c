/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include "uart.h"
#include <stdint.h>


void uart_init(void){
  SYSCTL_RCGCGPIO_R |= 0x2;  //enable clock to GPIO port B
  SYSCTL_RCGCUART_R |= 0x2;  //enable clock to UART1

  while ((SYSCTL_PRGPIO_R & 0x2) == 0) {};  //wait for GPIOB and UART1 peripherals to be ready
  while ((SYSCTL_PRUART_R & 0x2) == 0) {};  //wait for GPIOB and UART1 peripherals to be ready

  GPIO_PORTB_AFSEL_R |= 0x3;  //enable alternate functions on port B pins
  GPIO_PORTB_DEN_R |= 0x3;  //enable digital functionality on port B pins
  GPIO_PORTB_PCTL_R = 0x11;  //enable UART1 Rx and Tx on port B pins

  uint16_t iBRD = 8;
  uint16_t fBRD = 44;

  UART1_CTL_R &= 0xFFFFFFFE;  //turn off UART1 while setting it up

  //set baud rate
  //note: to take effect, there must be a write to LCRH after these assignments
  UART1_IBRD_R = iBRD;
  UART1_FBRD_R = fBRD;

  //set frame, 8 data bits, 1 stop bit, no parity, no FIFO
  //note: this write to LCRH must be after the BRD assignments
  UART1_LCRH_R = 0x60;
  UART1_CC_R = 0x0;
  UART1_CTL_R |= 0x1;

}

void uart_sendChar(char data){
	while((UART1_FR_R & 0x20) != 0);
	UART1_DR_R=data;
	return;
}

char uart_receive(void){
    char ret;
	while((UART1_FR_R & 0x10) != 0);
	ret = UART1_DR_R & 0xFF;
	uart_sendChar(ret);
	return ret;
}

void uart_sendStr(const char *data){

}

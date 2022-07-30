/*
 * uart.h
 *
 * Created: 2022-07-29 오전 10:46:34
 *  Author: KCCI03
 */ 

#ifndef UART_H_
#define UART_H_
#define F_CPU 14745600L
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

void uart_init(void);
void UART0_transmit(char data);
uint8_t UART0_receive(void);
void UART1_transmit(char data);
uint8_t UART1_receive(void);
void Trs(char* data);
void get_msg(char *msg);
int parsing(char *msg);

#endif /* UART_H_ */
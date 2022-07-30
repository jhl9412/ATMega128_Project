/*
 * uart.c
 *
 * Created: 2022-07-29 오전 10:46:22
 *  Author: KCCI03
 */ 

#include "uart.h"
#include "lcd.h"
#include <stdlib.h>
int dis_r, dis_l, temp, humi;
void uart_init(void)
{
// 	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
// 	UBRR0L = 95;
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	UBRR1L = 95;
}

void UART0_transmit(char data)
{
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

uint8_t UART0_receive(void)
{
	while(!(UCSR0A & (1<<RXC1)));
	return UDR0;
}
void UART1_transmit(char data)
{
	while(!(UCSR1A & (1<<UDRE1)));
	UDR1 = data;
}

uint8_t UART1_receive(void)
{
	while(!(UCSR1A & (1<<RXC1)));
	return UDR1;
}

void Trs(char* data) {
	while(*data != 0x00) {
		UART0_transmit(*data);
		data++;
		_delay_ms(10);
	}
}

void get_msg(char* msg)
{
	int i = 0;
	do{
		msg[i] = UART1_receive();
		_delay_ms(1);
	}
	while(msg[i++]!='\n');
	msg[i-2] = '\0';
	//Trs(msg);

	parsing(msg);
}

int parsing(char *msg)
{
	int j = 0;
	char *ptr = NULL;
	char par[4][10];

	ptr = strtok(msg, "L");
	while( ptr != NULL )
	{
		strcpy(par[j++],ptr);
		ptr = strtok(NULL, "L");
		
	}
	if(par[0]=='\0') return -1;

	dis_r = atoi(par[0]);
	dis_l = atoi(par[1]);
	temp = atoi(par[2]);
	humi = atoi(par[3]);
	
// 	for(int idx = 0; idx<4; idx++)
// 	{
// 		memset(par[idx],'\0',10);
// 	}
	return 0;	
}

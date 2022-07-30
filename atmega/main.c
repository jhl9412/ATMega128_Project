#define F_CPU 14745600L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>


unsigned char font[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d,0x7c,0x07,
	0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e,0x79,0x71,
0x08,0x80};

int t_cnt = 0;
int m_cnt = 10;
int AngleCount = 0;
int flag = 0;
char msg[30]={0};


void UART0_transmit(char data);
uint8_t UART0_receive(void);
void UART1_transmit(char data);
uint8_t UART1_receive(void);
void Trs(char *data);
void segment(int n);
void Servo(int);

ISR(TIMER2_COMP_vect);
//ISR(INT0_vect)
//{
	//
//}
//ISR(INT1_vect)
//{
	//
//}
int main(void)
{
	//servo setting
	DDRB = 0x90;//90
	PORTB = 0x80;
	AngleCount = 15; // 초기 서보 위치 0도 설정
	//fnd setting
	DDRA = 0xff;
	DDRC = 0x0f;
	PORTA = 0xff;
	PORTC = 0x0f;
	//timer setting
	TCCR2 = (1<<CS00) |(1<<CS02) |(1<<CS01) | (1<<COM00) | (1<<WGM01); // ctc toggle // prescaler 8
	TIMSK = 1<<OCIE0; // output compare
	TCNT0 = 0;
	OCR0 = 184; // prescaler 8 010 => 0.1ms
	
	//uart setting
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UBRR0L = 95; 
	UCSR1B = (1<<RXEN1) | (1<<TXEN1);
	UBRR1L = 95;
	//interrupt setting : 0,1 rising edge
	EIMSK = 1<<INT0 | 1<<INT1;
	EICRA = 1<<ISC00 | 1<<ISC01 | 1<<ISC10 | 1<<ISC11; 
	
	int dis_r, dis_l, temp, humi;
		
	sei();
	while (1)
	{
		int i = 0, j = 0;
		do{
			msg[i] = UART1_receive();
			UART0_transmit(msg[i++]);
			_delay_ms(1);
		}
		while(msg[i-1]!='\n');
		
		char *ptr = NULL;
		char par[4][10];

		ptr = strtok(msg, "L");
		while( ptr != NULL )
		{
			strcpy(par[j++],ptr);
			ptr = strtok(NULL, "L");
					
		}
		for(int idx = 0; idx<4; idx++){
			Trs(par[idx]);
			_delay_ms(100);
			Trs("\r\n");
			_delay_ms(100);
		}
		dis_r = atoi(par[0]);
		dis_l = atoi(par[1]);
		temp = atoi(par[2]);
		humi = atoi(par[3]);
		for(int idx = 0; idx<4; idx++)
		{
			memset(par[idx],'\0',10);
		}
		
		Servo(0);
		_delay_ms(1000);
		
		Servo(90);
		_delay_ms(1000);
		
		Servo(-90);
		_delay_ms(1000);
		
		memset(msg, '\0', sizeof(msg));
	}	
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

void Trs(char *data) {
	while(*data != 0x00) {
		UART1_transmit(*data);
		data++;
//		_delay_ms(50);
	}
}

ISR(TIMER0_COMP_vect)
{

	t_cnt++;
	if((flag == 0)&&(t_cnt == AngleCount))
	{
		PORTB &= 0xef;
		flag=1;
	}
	else
	{
		if(t_cnt == 200){
			PORTB |= 0x10;
			t_cnt = 0;
			flag=0;
		}
	}
}

void segment(int n)
{
	unsigned char n1000, n100, n10, n1;
	int buff;
	n1000 = n / 1000;
	buff = n % 1000;
	n100 = buff / 100;
	buff = buff % 100;
	n10 = buff / 10;
	n1 = n % 10;
	
	for(int i = 0; i< 10; i++)
	{
		PORTC = 0x0e;
		PORTA = font[n1000];
		_delay_ms(1);
		PORTC = 0x0d;
		PORTA = font[n100];
		_delay_ms(1);
		PORTC = 0x0b;
		PORTA = font[n10];
		_delay_ms(1);
		PORTC = 0x07;
		PORTA = font[n1];
		_delay_ms(1);
	}
}

void Servo(int Angle)
{
	if(Angle == -90)
		AngleCount=7; //pwm on time 2.3ms
	else if(Angle == 0)
		AngleCount = 15; //pwm on time 1.5ms
	else if(Angle == 90)
		AngleCount  = 21; //pwm on time 0.7ms	
}
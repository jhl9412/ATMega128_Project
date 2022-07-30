/*
 * servo.c
 *
 * Created: 2022-07-29 오전 11:01:25
 *  Author: KCCI03
 */ 

#include "servo.h"
#include "lcd.h"
#include <stdio.h>
int  r_cnt = 0, l_cnt = 0;
extern int dis_r, dis_l, temp, humi;
int angle = 20;
int m_speed;
void servo_init(void)
{
	DDRB = 0x90; // PB4,7
	PORTB = 0X90;
	TCCR0 = (1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS01)|(1<<CS02) | (1<<CS00);
	TCCR2 = (1<<CS22) |(1<<CS20) | (1<<COM21) | (1<<WGM21)| (1<<WGM20);

	TIMSK = (1<<OCIE2);
	OCR2 = 255; // 0.1ms;
	OCR0 = 120;
}
void servo(void)
{

	OCR2 = angle;
	_delay_ms(10);
	
 	set_speed();
 	dc_run();
	//_delay_ms(100);
}

void set_speed(void)
{
	if((humi>50)||(temp>=20))
	m_speed = 250;
	//else if(temp<30&&temp>=20)
	//m_speed = 150;
}

void dc_run()
{
	if((dis_r <= 100 && dis_r > 50) || (dis_l <= 100 && dis_l > 50))
	{
		OCR0 = m_speed;
	}
	else if((dis_r <= 50 && dis_r > 10) || (dis_l <= 50 && dis_l > 10))
	{
		OCR0 = m_speed-50;
	}

}
 
 ISR(TIMER2_COMP_vect)
 {

	if(dis_r <= 20)					r_cnt++;
	else if(dis_r>20&&dis_r<2000)	r_cnt = 0;
	if(dis_l <= 20)					l_cnt++;
	else if(dis_l>20&&dis_l<2000)	l_cnt = 0;

	if(r_cnt > 50)
	{
		l_cnt = 0;
		angle--;
		if(angle <= 9) 	angle = 9;
		r_cnt = 0;
	}
	 	
	if(l_cnt > 50)
	{
		r_cnt =0 ;
		angle++;
		if(angle >= 33) angle = 33;
		l_cnt = 0;
	}
 }

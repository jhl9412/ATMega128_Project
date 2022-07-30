/*
 * servo.h
 *
 * Created: 2022-07-29 오전 11:01:14
 *  Author: KCCI03
 */ 


#ifndef SERVO_H_
#define SERVO_H_
#define F_CPU 14745600L
#include <avr/interrupt.h>
#include <util/delay.h>
void servo_init(void);
void servo(void);
void set_speed(void);
void dc_run();
/*ISR(TIMER2_COMP_vect);*/

#endif /* SERVO_H_ */
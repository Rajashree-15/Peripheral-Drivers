/*
 * PWM.h
 *
 *  Created on: 03-Jun-2022
 *      Author: Rajashree
 */

#ifndef PWM_H_
#define PWM_H_

#include <avr/io.h>
#define PORTx      PORTD

void PWM_init()
{
	DDRD |= _BV(PD6) | _BV(PD5) | _BV(PD3) | _BV(PD2) | _BV(PD7) | _BV(PD4);
	DDRB |= _BV(PB2);
	PORTD |= (1 << PORTD4) | (1 << PORTD7);
	TCCR1B |= _BV(WGM12) | _BV(CS10) | _BV(CS11);//TIMER 1 PWM1 //prescalar 64
	TCCR2B |= _BV(CS20) | _BV(CS21);//TIMER 2 PWM2 //prescalar 64
	TCCR0B |= _BV(CS00) | _BV(CS01);//|_BV(CS01);//TIMER 0 PWM3 and PWM4 Prescaler scaled by 64

}
//PWM Frequency = F(clk_io)/(N*256), N is the prescalar value, F(clk_io)=16MHz,N=64, F=976Hz
//For N=1 F=62.5KHz N=8 F=7.81KHz N=64 F=976Hz N=256 F=244Hz N=1024 F=61Hz
void PWM1_NonInv()
{
	TCCR1A = _BV(COM1B1) | _BV(WGM10);
}
void PWM2_NonInv()
{
	TCCR2A = _BV(COM2B1) | _BV(WGM20) | _BV(WGM21);
}
void PWM3_NonInv_PWM4_Inv()
{
	TCCR0A = _BV(COM0B1) | _BV(COM0A0) | _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
}
void PWM4_NonInv_PWM3_Inv()
{
	TCCR0A = _BV(COM0B1) | _BV(COM0B0) | _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
}
void PWM4_Inv_PWM3_Inv()
{
	TCCR0A = _BV(COM0B1) | _BV(COM0B0) | _BV(COM0A0) | _BV(COM0A1) | _BV(WGM00) | _BV(WGM01);
}
void PWM1_Inv()
{
	TCCR1A = _BV(COM1B1) | _BV(COM1B0) | _BV(WGM10) | _BV(COM1A1);
}

void PWM2_Inv()
{
	TCCR2A = _BV(COM2B1) | _BV(COM2B0) | _BV(WGM20) | _BV(WGM21);
}

int PWM_duty(int duty_count)
{
	int duty;
	if (duty_count == 2)
		duty = 0x3F;//25%
	if (duty_count == 3)
		duty = 0X7F;//50%
	if (duty_count == 4)
		duty = 0xBF;//75%
	if (duty_count == 5)
		duty = 0xFF;//100%
	return duty;
}
#endif /* PWM_H_ */

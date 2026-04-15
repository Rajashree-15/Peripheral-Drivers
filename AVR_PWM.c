/*
 * main.c
 *
 *  Created on: 20-April-2022
 *      Author: Rajashree
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#define PORTx       PORTD

/*
 * TCCRnx are timer registers.Eg:TCCR0A TCCR0B correspond to Timer0.
 * TCCRnA is used to set the PWM mode(normal mode, CTC,Fast PWM, Phase correct PWM) according to the truth table given in the
 * datasheet using WGMXX bits.COMnXX bits are used to set the PWM output mode in inverted or non-inverted mode according to the
 * truth table.
 * TCCRnB is used to set the clock frequency for the PWM using CSnX bits.
 */
void PWM_init()
{
	DDRD |= _BV(PD6);
	DDRD |= _BV(PD5);
	DDRD |= _BV(PD3);
	DDRD |= _BV(PD2)|_BV(PD4)|_BV(PD7);
	DDRB |= _BV(PB2);
	PORTD |= (1<<PORTD4) | (1<<PORTD7);

    //frequency of the PWM is set to 7.8KHz according to fast pwm mode and clock prescalar value is set to 8 for all the timers

	TCCR0A = _BV(COM0A1)|_BV(WGM00) | _BV(WGM01)|_BV(COM0B1);//timer0 settings
	TCCR0B |= _BV(CS01);
	TCCR2B |= _BV(CS21);
    TCCR2A |= _BV(COM2A1) | _BV(WGM20) | _BV(WGM21)|_BV(COM2B1);
    TCCR1A |= _BV(WGM10) | _BV(COM1A1)| _BV(COM1B1);
    TCCR1B |= _BV(WGM12) |_BV(CS11);
}


    int main ()
    {
    	PWM_init();
    	uint8_t duty=0XFF; bool up=true;
    	for(;;)
    	{
    		duty += up ? 1 : -1;
    				if (duty == 0xFF)
    					up = false;
    				else if (duty == 0x00)
    					up = true;

    		OCR0A = duty;
		    OCR0B = duty;
		    OCR2B = duty;
	        OCR1B = duty;


	}

}

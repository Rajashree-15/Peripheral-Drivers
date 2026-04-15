/*
 * main.c
 *
 *  Created on: 19-Sept-2022
 *      Author: Rajashree
 */
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#define USART_BAUDRATE 9600
#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
#define PORTx      PORTD

void PWM_init ()
 {
	    DDRD |= _BV(PD6)|_BV(PD5)|_BV(PD3)|_BV(PD2)|_BV(PD4)|_BV(PD7);//make the PWM pions as output pins
	    DDRB |= _BV(PB2);//make PB2 pin as output
            PORTD|= (1<<PORTD4) | (1<<PORTD7);
            TCCR0A = _BV(COM0A1)|_BV(WGM00) | _BV(WGM01)|_BV(COM0B1);//Non inverting mode PWM on all PWM channels, fast PWM MODE
	    TCCR0B |= _BV(CS01);
	    TCCR2B |= _BV(CS02);
	    TCCR2A |= _BV(COM2A1) | _BV(WGM20) | _BV(WGM21)|_BV(COM2B1);
	    TCCR1A |= _BV(WGM10) | _BV(COM1A1)| _BV(COM1B1);
	    TCCR1B |= _BV(WGM12) |_BV(CS10);
	    OCR0A = 0x7F;//PWM4 on pin PD6--GREEN , duty=50% on all PWM channels
	    OCR0B = 0x7F; //PWM3 on pin PD5--ORANGE
	    OCR2B = 0x7F;//PWM2 on pin PD3--RED
	    OCR1B = 0x7F;//PWM1 on pin PB2--YELLOW
}
void USART0Init(void)
{
// Set baud rate
UBRR0H = (uint8_t)(UBRR_VALUE>>8);
UBRR0L = (uint8_t)UBRR_VALUE;
// Set frame format to 8 data bits, no parity, 1 stop bit
UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
//enable transmission and reception
UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
}
int USART0SendByte(char u8Data, FILE *stream)
{
   if(u8Data == '\n')
   {
        USART0SendByte('\r', stream);
   }
//wait while previous byte is completed
while(!(UCSR0A&(1<<UDRE0))){};

// Transmit data
UDR0 = u8Data;
return 0;
}
//set stream pointer
FILE usart0_str = FDEV_SETUP_STREAM(USART0SendByte, NULL, _FDEV_SETUP_WRITE);
void InitADC()
{
    // Select Vref=AVcc
    ADMUX |= (1<<REFS0);
    //set prescaller to 128 and enable ADC
    ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}
uint16_t ReadADC(uint8_t ADCchannel)
{
    //select ADC channel with safety mask
    ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);
    //single conversion mode
    ADCSRA |= (1<<ADSC);
    // wait until ADC conversion is complete
    while( ADCSRA & (1<<ADSC) );
   return ADC;
}
int main()
{
double  adc_val;
PWM_init ();
//initialize ADC
InitADC();
//Initialize USART0
USART0Init();
//assign our stream to standart I/O streams
stdout=&usart0_str;
while(1)
{
    adc_val=ReadADC(0);
    printf("ADC value = %u \n", (uint16_t)adc_val);
    _delay_ms(5000);
   }
}

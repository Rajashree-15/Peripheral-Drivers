/*
 * main.c
 *
 *  Created on: 26-Sep-2022
 *      Author: Rajashree
 */
#define F_CPU 16000000UL // Defining the CPU Frequency

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Generates a Blocking Delay
#include <stdio.h>

#include <avr/interrupt.h>
#include <stdbool.h>


#define USART_BAUDRATE 9600 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection


#define PORTx       PORTD
void USART_Init()
{
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;

	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;

	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

uint8_t USART_ReceivePolling()//UART Receiving function
{
	uint8_t DataByte;
	while (( UCSR0A & (1<<RXC0)) == 0) {}; // Do nothing until data have been received
	DataByte = UDR0 ;
	return DataByte;
}
void USART_TransmitPolling(uint8_t DataByte)//UART Transmitting function
{
	while (( UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
	UDR0 = DataByte;
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
void pwm_init()
{
	DDRD |= _BV(PD6)|_BV(PD5)|_BV(PD3)|_BV(PD2)|_BV(PD4)|_BV(PD7);
	DDRB |= _BV(PB2);
	PORTD |= (1<<PORTD4) | (1<<PORTD7);
	TCCR0A = _BV(COM0A1)|_BV(WGM00) | _BV(WGM01)|_BV(COM0B1);
	TCCR0B |= _BV(CS01);//timer1 clock prescalar is 8
	TCCR2B |= _BV(CS21);//timer2 clock prescalar is 8
	TCCR2A |= _BV(COM2A1) | _BV(WGM20) | _BV(WGM21)|_BV(COM2B1);
	TCCR1A |= _BV(WGM10) | _BV(COM1A1)| _BV(COM1B1);
	TCCR1B |= _BV(WGM12) |_BV(CS11);//timer1 clock prescalar is 8
}
/*
 * The following code is written for timer0 channel A,it can be changed to timer1 or timer2.All the PWM channels are initialized
 * to fast pwm mode with pwm frequency calculated using the equation in the datasheet.PWM frequency=7.81khz for clock prescalar=8,
 * and clock frequency = 16 MHz.
 */
int main()
{
	//UART
	USART_Init();
	stdout=&usart0_str;
	char LocalData;uint8_t duty=0;
	//PWM
	pwm_init();
	OCR0A=0X7F;//By default the duty cycle of the PWM is set to 50%
	while (1)
	{
		LocalData = USART_ReceivePolling();
		if(LocalData=='1')
			{
			duty=25;
			OCR0A = 0x3F;
			}
		if(LocalData=='2')
		{
			duty=50;
			OCR0A = 0x7F;
		}
		if(LocalData=='3')
		{
			duty=75;
			OCR0A = 0xBF;
		}
		if(LocalData=='4')
		{
			duty=100;
			OCR0A = 0xFF;
		}
		printf("duty = %u \n",duty);
		//USART_TransmitPolling(LocalData);//this line can be uncommented to send the received data back to the UART device(ESP32)
	}
	return 0;
}

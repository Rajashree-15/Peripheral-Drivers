The programs given here should be added to a main.c(source file) file of the project.
'AVR_UART.txt' - This program transmits a 'HELLO' message to UART Receiver
'AVR_PWM.txt'  - This program generates a PWM signal with varying duty ratio
'PWM_duty_control.txt - This program generates a PWM signal of a duty ratio specified by a UART Transmitter.(can be used to control the duty via http client when ESP32 is programmed as a http server)
'SINE_PWM.txt' - This program generates 3 phase sinusoidal pulse width modulated signal with carrier frequency=7.8KHz, No of                        samples=156,Frequency of modulating sine wave=50Hz
'SINE_PWM_amplitude_control.txt"- This program generates 3 phase sinusoidal pulse width modulated signal with carrier                                                frequency=7.8KHz, No of samples=156,Frequency of modulating sine wave=50Hz whose 
                                  amplitude can be specified by a UART Transmitter.(This program can be used to control the amplitude of the SINE PWM via http client when ESP32 is programmed as a http server)
'ADC_UART.txt' - This program reads the Analog input to the ADC port of the microcontroller and converts it to the digital data 
and transmits the same to the UART receiver(can be a serial monitor).

'Stepper_motor_fullstep.txt'- This program generates PWM to drive the stepper motor in the full step mode
'Stepper_motor_halfstep.txt'- This program generates PWM to drive the stepper motor in the half step mode
'Stepper_motor_microstepping.txt'- This program generates PWM to drive the stepper motor in the microstepping mode

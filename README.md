# AVR Embedded Programs Collection

## Overview
This repository contains a set of AVR-based programs demonstrating key embedded system functionalities such as UART communication, PWM generation, ADC interfacing, sinusoidal PWM (SPWM), and stepper motor control.

All programs are intended to be integrated into a single `main.c` file depending on the application requirements.

---

## Programs Included

### UART Communication
- **AVR_UART.txt**  
  Sends a "HELLO" message to a UART receiver.

- **ADC_UART.txt**  
  Reads analog input from the ADC pin, converts it to digital data, and transmits the result via UART (e.g., to a serial monitor).

---

### PWM Generation
- **AVR_PWM.txt**  
  Generates a PWM signal with a varying duty cycle.

- **PWM_duty_control.txt**  
  Generates a PWM signal where the duty cycle is controlled via UART input.  
  This can be extended for remote control using an ESP32 configured as an HTTP server.

---

### Sinusoidal PWM (SPWM)
- **SINE_PWM.txt**  
  Generates a 3-phase sinusoidal PWM signal with:
  - Carrier frequency: 7.8 kHz  
  - Number of samples: 156  
  - Output sine wave frequency: 50 Hz  

- **SINE_PWM_amplitude_control.txt**  
  Generates a 3-phase SPWM signal with adjustable amplitude via UART input.  
  Suitable for remote control applications (e.g., ESP32 HTTP server integration).

---

### Stepper Motor Control
- **Stepper_motor_fullstep.txt**  
  Drives a stepper motor in full-step mode.

- **Stepper_motor_halfstep.txt**  
  Drives a stepper motor in half-step mode for smoother motion.

- **Stepper_motor_microstepping.txt**  
  Drives a stepper motor using microstepping for precise control and reduced vibration.

---

## Usage
- Add the required program(s) into your `main.c` file.
- Initialize necessary peripherals such as UART, ADC, and Timers before use.
- Modules can be used independently or combined based on your project needs.

---

## Notes
- UART-based programs can interface with serial monitors or external controllers like ESP32.
- Ensure correct hardware connections and clock configurations before running the code.

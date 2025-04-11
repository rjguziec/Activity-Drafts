#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

// Encoder Count Variables
volatile unsigned int leftWheelCount = 0;
volatile unsigned int rightWheelCount = 0;

// Wheel Constants (Adjust Based on Encoder Specifications)
#define WHEEL_CIRCUMFERENCE 0.650  // In meters (65 cm)
#define ENCODER_TICKS_PER_REV 192  // Number of encoder pulses per revolution

void setup() {
  cli();  // Disable global interrupts

  // Configure A4 (PC4) and A5 (PC5) as inputs (Wheel Encoders)
  DDRC &= ~(0x30);  // PC4 (0x10), PC5 (0x20) as inputs

  // Enable Pull-Up Resistors
  PORTC |= 0x30;  // Enable pull-ups on PC4 and PC5

  // Configure External Interrupts on Falling Edge for A4 (PC4) and A5 (PC5)
  PCICR |= 0x02;   // Enable Pin Change Interrupt for PCINT[14:8] (Port C)
  PCMSK1 |= 0x30;  // Enable PCINT12 (A4) and PCINT13 (A5)

  // Configure Timer1 for PWM Motor Control (OC1A, OC1B)
  DDRB |= 0x06;   // PB1 (0x02) & PB2 (0x04) as outputs (PWM)
  TCCR1A = 0xA1;  // Fast PWM, Clear OC1A/OC1B on Compare Match
  TCCR1B = 0x0A;  // Prescaler = 8, WGM Mode 14 (Fast PWM)
  ICR1 = 39999;   // (16 MHz / (8 * 50 Hz)) - 1

  // Set Initial PWM Duty Cycle (50%)
  OCR1A = 19999;  // 50% duty cycle
  OCR1B = 19999;  // 50% duty cycle

  sei();  // Enable global interrupts

  // Initialize Serial Communication
  UCSR0B = 0x18;  // Enable TX and RX
  UCSR0C = 0x06;  // 8-bit data, 1 stop bit
  UBRR0L = 103;   // 9600 Baud Rate (assuming 16MHz clock)
}

ISR(PCINT1_vect) {
  // Detect Falling Edge on A4 (Left Wheel Encoder)
  if (!(PINC & 0x10)) {
    leftWheelCount++;
  }

  // Detect Falling Edge on A5 (Right Wheel Encoder)
  if (!(PINC & 0x20)) {
    rightWheelCount++;
  }
}

void loop() {
  // Calculate Average Encoder Ticks
unsigned int averageTicks = (leftWheelCount + rightWheelCount) / 4;

  // Calculate Distance Traveled
  float distanceTraveled = (averageTicks / 192) * WHEEL_CIRCUMFERENCE;
  
  


  // Display on Serial Monitor
  char buffer[50];
  sprintf(buffer, "Left: %u, Right: %u, Distance: %u m\n", leftWheelCount, rightWheelCount, distanceTraveled);
  
  Serial.println(distanceTraveled);  //mass display
  //Serial.print(distanceTraveled);
  for (char* ptr = buffer; *ptr; ptr++) {
    while (!(UCSR0A & 0x20))
      ;           // Wait until UART is ready
    UDR0 = *ptr;  // Send character
  }

  _delay_ms(500);  // Update rate
}
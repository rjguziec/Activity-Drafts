/*
  Activity 10
  By: R
  Written: February 24, 2025
  I/O Pins
  A0: TMP36
  A1:
  A2:
  A3:
  A4:
  A5:
  D0:
  D1: 
  D2: Direction bit
  D3: 
  D4: 
  D5: 
  D6: 
  D7: 
  D8: 
  D9: 
  D10: 
  D11: 
  D12: 
  D13:
*/

// Optional: preserve status register
volatile unsigned char statusVariable = 0;

void setup() {
  cli();  // Disable global interrupts

  // ----------- TIMER1 CONFIG FOR PWM -----------
  // Fast PWM, 10-bit, Clear OC1A and OC1B on Compare Match
  TCCR1A = 0xA3;  // COM1A1/COM1B1 = 1, WGM11:WGM10 = 11 (10-bit)
  TCCR1B = 0x11;  // WGM13:WGM12 = 01 (for mode 7), Prescaler = 1
  TCCR1C = 0x00;
  TIMSK1 = 0x00;

  // Set PB1 (D9) and PB2 (D10) as outputs
  DDRB = 0x06;  // 0b00000110 = PB1 and PB2 output

  // ----------- ADC CONFIG FOR POTENTIOMETER (A0) -----------
  ADMUX = 0x40;   // pot reference, ADC0
  ADCSRA = 0xEF;  // ADC Enable, Start, Auto Trigger, Interrupt, Prescaler = 128
  ADCSRB = 0x00;  // Free Running Mode

  // ----------- CONFIGURE DIRECTION SWITCH ON D2 (PD2) -----------
  EICRA = 0x01;  // External change interupt, changes value per pin change
  eimsk = 0x01;  // D2

  sei();  // Enable global interrupts
}

void loop() {
  // Nothing needed here, all logic handled in ADC ISR
}

ISR(ADC_vect) {
  statusVariable = SREG;

  // Read direction switch state
  unsigned char direction = (PIND & 0x04);  // Read PD2 (D2)

  // Scale ADC to 10-bit PWM: 0-1023 to 64–320 (20% to 100%)
  unsigned int pwmValue = ((ADC * 256UL) >> 10) + 64;

  // Set direction and update PWM output
  if (direction == 0) {
    // Switch pressed (LOW): reverse
    OCR1A = pwmValue;  // Drive reverse on D9 (OC1A)
    OCR1B = 20000;         // Turn off forward
  } else {
    // Switch not pressed: forward
    OCR1B = pwmValue;  // Drive forward on D10 (OC1B)
    OCR1A = 20000;         // Turn off reverse
  }

  SREG = statusVariable;
}

ISR(INT0_vect)
{
  direction ^= 1;
}
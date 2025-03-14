/*
  Activity 9
  Testing PWM on Timercounter 0
  By: Robert J Guziec, Jacob Horstman, Sasha Dauz
  Written: March 14, 2025
  Edited: March 14, 2025
  I/O Pins
  A0: POT
  A1:
  A2:
  A3:
  A4:
  A5:
  D0:
  D1:  
  D2:  
  D3:  
  D4:  
  D5:  Nice box! 
  D6:  Absolute SHIT 
  D7:  
  D8:  
  D9:  
  D10: 
  D11: 
  D12:
  D13:
*/

void setup() {
  cli();
  TCCR0A = 0xA3; // Think we got this good! 
  TCCR0B = 0x0B; // Good :D
  TIMSK0 = 0x04; // Comparing on B :O  

  OCR0A = 0xFE;
  OCR0B = 0xEF;

  DDRD = 0x30;
  sei();
}

void loop() {
  
}

/* We don't think we need this, but we wrote it :3
volatile unsigned char greg = 0;

ISR(TIMER0_COMPB_vect){
  greg = SREG;
  SREG = greg;
}
*/

/*
  Activity 9 Circuit 3
  Testing PWM on Timercounter 1
  We have no idea how this works, it just runs on magic!
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
  D5:  
  D6: 
  D7:  
  D8:  
  D9:  A is disconnected, normal port mode
  D10: Output B
  D11: 
  D12:
  D13:
*/

void setup() {
  cli();
  // When using Phase shift, your OCRnA is your TOP or PseudoMAX
  // OCRAnB is the your pulse (your TOP)
  
  TCCR1A = 0x23; // bad? Needs attention, idk anymore bro
  TCCR1B = 0x11; // prescaler 1
  TCCR1C = 0x00; // WTF is this register???????
  
  TIMSK1 = 0x00; // good  

  OCR1A = 320; // Writing to our 16 bit register in decimal value!
  OCR1B = 64;  // Funny number magic man 
  
  DDRB = 0x04; // OUTPUT so we can see the p a i n 
  sei();
}

void loop() {
  
}
/*
//We don't think we need this, but we wrote it :3
volatile unsigned char greg = 0;

ISR(TIMER1_COMPA_vect){
  greg = SREG;
  SREG = greg;
}
*/

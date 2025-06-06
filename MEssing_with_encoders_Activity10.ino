
/*
  Messing with Activity 10
  Using Pin Change interrupts to determine if our wheel has moved.
  By: Robert Guziec, Jacob Horstman
  Written: March 20, 2025
  Edited: March 20, 2025
  I/O Pins
  A0: 
  A1:
  A2:
  A3:
  A4: 
  A5: Wheel Encoder
  D0:
  D1:
  D2:
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

void setup() {
  cli();

  PCICR = 0x02;  // Enable pin change on register C
  PCMSK1 = 0x30; // Mask for pins A4 and A5

  PORTC |= 0x10;  // Enable internal resistor on pin A4

  Serial.begin(9600);
  sei();
}

volatile int wheelRead = 0; // Counter variable for encoder

void loop() {

}

ISR(PCINT1_vect){
  wheelRead++;
  Serial.println(wheelRead);
}


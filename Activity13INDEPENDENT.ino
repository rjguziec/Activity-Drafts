/*
 Title: Activity 13 (Independent SS pins)
 Desc: Using SPI, write to 4 74595 shift registers to write to 4 seven segment display
       displaying the ADC value from a potentiometer using independent SS pins.
  By: Robert Guziec
  Written: May 9, 2025
  I/O Pins
  A0: SS1
  A1: SS2
  A2: SS3
  A3: SS4
  A5: POT DURING TEST
  D11: MOSI (SER (pin 14))
  D12: MISO (QH')
  D13: SCK (SRCLK (pin 11))
*/

void setup() {

  cli();
  
  DDRB = 0x2C;   // SCK, MOSI, SS configuration for PRIMARY
  
  DDRC = 0x0F;   // Independent SS pins
  PORTC |= 0x0F;  // SS pin ACTIVE LOW!!!!
  
  // Configure ADC
  ADCSRA = 0xE7;
  ADCSRB = 0x00;
  ADMUX = 0x45;

  // Configure SPCR ONLY
  SPCR = 0x70;
  sei();

}

void loop() {

   // Cool local variables
   unsigned int potVal = ADC;

  //Array of 7 segment Display key and value array to be written
  unsigned char numArray[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
  unsigned char valueArray[4] = {numArray[potVal % 10], numArray[((potVal) / 10) % 10], numArray[((potVal) / 100) % 10], numArray[(potVal / 1000)]};

  // For loop that writes through each SS
  for (unsigned char i = 0; i < 4; i++){
    PORTC &= ~(1 << i);
    writeToSPI(valueArray[i]);
    PORTC |= 0x0F;
  }
  _delay_ms(50);
}


// Write to SPI
void writeToSPI(char dataToWrite){
    SPDR = dataToWrite;
    while (!(SPSR & (1 << SPIF)));  // Wait until transfer is complete
}

/*
 Title: Activity 13 (DAISY CHAINED)
 Desc: Using SPI, write to 4 74595 shift registers to write to 4 seven segment display
       displaying the ADC value from a potentiometer.
  By: Robert Guziec
  Written: May 9, 2025
  I/O Pins
  A0: POT DURING TEST
  D10:  SS (RCLK (pin 12))
  D11: MOSI (SER (pin 14))
  D12: MISO (QH')
  D13: SCK (SRCLK (pin 11))
*/

void setup() {

  DDRB = 0x2C;   // SCK, MOSI, SS configuration for PRIMARY
  PORTB |= 0x40; // SS High

  cli();
  // Configure ADC
  ADCSRA = 0xE7;
  ADCSRB = 0x00;
  ADMUX = 0x40;

  // Configure SPCR ONLY
  SPCR = 0x70;
  
  sei();

  Serial.begin(9600);
  
}

void loop() {

   // Cool local variables
   unsigned char ones = 0;
   unsigned char tens = 0;
   unsigned char hunds = 0;
   unsigned char thous = 0;
   unsigned int potVal = ADC;

  //Arrary of 7 segment Display
  unsigned char numArray[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};

  // Break down into ones and tens place
  ones = (potVal % 10);
  tens = ((potVal - ones) / 10) % 10;
  hunds = ((potVal - tens - ones) / 100) % 10;
  thous = (potVal / 1000);

  writeToSPI(numArray[thous]);
  writeToSPI(numArray[hunds]);
  writeToSPI(numArray[tens]);
  writeToSPI(numArray[ones]);

  Serial.println(ones);
  _delay_ms(5);


}

// Write to SPI
void writeToSPI(int dataToWrite) {
  PORTB &= 0xFB; 
  
  SPDR = dataToWrite;
  while (!(SPSR & (1 << SPIF)));  // Wait until transfer is complete

  PORTB |= 0x04; 
}

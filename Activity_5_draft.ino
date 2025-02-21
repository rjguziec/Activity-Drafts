/*
  Activity 5
  Averaging Temperature Sensor Data
  By: Robert J Guziec, Jacob Horstman
  Written: Feb 21, 2025
  Edited: Fed 21, 2025
  I/O Pins
  A0: POT
  A1:
  A2:
  A3:
  A4:
  A5:
  D0:
  D1:  SEG G
  D2:  SEG F
  D3:  SEG E
  D4:  SEG D
  D5:  SEG C
  D6:  SEG B
  D7:  SEG A
  D8:  MUX1
  D9:  MUX2
  D10: MUX3
  D11: MUX4
  D12:
  D13:
*/


void setup()
{
  // Setup for our ADC
  ADCSRA = 0xE7;
  ADCSRB = 0x00;
  ADMUX = 0x40;

  // Setup for our output registers
  DDRD = 0xFE;
  DDRB = 0x0F;

}

void loop()
{

  // Declare circular buffer variable
  unsigned char cBuffer = 12;
  
  // Read ADC Value (YOUR INPUT)
  igned int adcr = ADC;

  // Define constants for our indexs and arrays
  const unsigned char n = 4;
  const unsigned char m = 10;

  // Mux arrive to write which Anode is active (ACTIVE LOW)
  unsigned char muxArray[n] = {0xF7, 0xFB, 0xFD, 0xFE};

  // Number arrive to write which segments are to be written
  unsigned char numArray[m] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6};

  // Read ones place of ADC
  unsigned int onePlace = (adcr % 10);
  // Read tens place of ADC
  unsigned int tenPlace = ((adcr - onePlace) / 10 % 10);
  // Read hundreds place of ADC
  unsigned int hundPlace = ((adcr - onePlace - tenPlace) / 100 % 10);
  // Read thousands place of ADC
  unsigned int thousPlace = (adcr / 1000 );

  // Array for which place to pull up
  unsigned int placeArray[n] = {onePlace, tenPlace, hundPlace, thousPlace};

  for (unsigned int i = 0; i < n; i++) {
    //Csll external fumction
    muxFunc( i, muxArray, numArray, placeArray);
  }
}

// Function writes and transkates values to the MUX Display
void muxFunc(int l, char muxVal[], char numVal[], int placeVal[]) {

  // Selective clear and go through mux values
  PORTB &= 0xF0;
  PORTB |= muxVal[l];

  // Selective clear and decipher numeric placce and value!
  PORTD &= 0x01;
  PORTD |= numVal[placeVal[l]];
  _delay_us(1000);
}

signed int ave(unsigned char k, signed int readADC)
{
  
  int sum = 0

  for (unsigned int j)

    sum += 
  }
}


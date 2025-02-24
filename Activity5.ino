/*
  Activity 5
  Didsplay ADC value onto an LCD screen
  By: Robert Guziec
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
  D2: 
  D3: 
  D4: 
  D5: 
  D6: 
  D7: 
  D8: R/S
  D9: E
  D10: DB4
  D11: DB5
  D12: DB6
  D13: DB7
*/

#include "hd44780.h"

// GROSS GLOBAL VARIABLES
// Declare circular buffer amount variable
const unsigned char N = 15;
// Create GLOBAL volatile variable for temperature values array
volatile unsigned int TEMPVAL[N] = {};

void setup() {
  // Configure ADC
  ADCSRA = 0xE7;
  ADCSRB = 0x00;
  ADMUX = 0x40;
  // Initialize LCD screen
  lcd_init();
}

void loop() {
  // Declare Ascii variable
  char asciiDeg = 223;

  // Calculate temperature from given ADC, provided page 49 of Lab Manual by Dr. P
  static unsigned char x = 0;
  int T = ((500L * ADC) >> 10) - 50;

  TEMPVAL[x] = T;
  x++;
  if (x==N){
    x=0;
  }

  // Clear screen
  lcd_clrscr();
  //Write string "Temperature:" on LCD
  lcd_puts("Temperature:");
  const char charBufferValue = 4;
  char charBuffer[charBufferValue];
  //Convert ADC result to a string, base 10
  itoa(ave(), charBuffer, 10);
  //Go to second line of LCD
  lcd_goto(40);
  //Display ADC result with units
  lcd_puts(charBuffer);
  lcd_putc(asciiDeg);
  lcd_puts("C");
  _delay_ms(50);
}

// Function that will calculate and return the average of sampled temperatures from loop
int ave(){
  // Initialize sum variable to zero
  unsigned int sum = 0;
  // For loop that iterates to calculate the average of collected data
  // from our array
  for(unsigned char j = 0; j < N; j++){
    sum += TEMPVAL[j];
  }

  sum /= N;
  return sum;
}





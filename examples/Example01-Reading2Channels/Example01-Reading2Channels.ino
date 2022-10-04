/*
 * Example01-Reading2Channels
 * 
 * Reads two channels from an ADS7142
 * 
 * Seth McNeill
 * 2022 October 03
 */
 
#include<Anitracks_ADS7142.h>

#define ADC_ADDR 0x1F  // ADS7142 I2C address

ADS7142 adc(ADC_ADDR); // Create ADS7142 object

void setup() {
  Serial.begin(115200);
  // Wait for serial to begin on some processors (RP2040)
  delay(3000);  
  Serial.println("Starting...");

  adc.begin();
}

void loop() {
  uint16_t adcIn1;
  uint16_t adcIn2;

  // adcIn1 and adcIn2 are passed by 
  // reference (&adcIn1) so that read2CH
  // can modify them. This is one way to
  // return multiple values from a function.
  if(!adc.read2Ch(&adcIn1, &adcIn2)) {
    Serial.println("adc failed");
  }
  // NOTE: The return values are 16-bit numbers
  // created by shifting the 12-bit ADC result
  // left by 4-bits. This becomes clearer if you
  // print the output in HEX and note the last
  // digit is always zero.
  Serial.print(adcIn1);
  Serial.print(", ");
  Serial.println(adcIn2);
  delay(1000);
}

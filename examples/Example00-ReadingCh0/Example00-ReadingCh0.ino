/* Example00-ReadingCh0.ino
 * 
 * Demonstrates/tests reading one input on the ADS7142.
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
  uint16_t adcIn;

  // readFirst returns the value from the voltage
  // attached to the AIN0 pin.
  // adcIn is passed by reference (&adcIn) so 
  // that read1Conversion can modify it.
  // This allows a status to be returned, indicating
  // whether the conversion was successful.
  if(!adc.readFirst(&adcIn)) {
    Serial.println("adc failed");
  }
  // NOTE: The return values are 16-bit numbers
  // created by shifting the 12-bit ADC result
  // left by 4-bits. This becomes clearer if you
  // print the output in HEX and note the last
  // digit is always zero.
  Serial.println(adcIn);
  delay(1000);
}

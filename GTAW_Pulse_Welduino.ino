/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>
// this code requires the Adafruit_MCP4725 library to be installed:
// https://learn.adafruit.com/mcp4725-12-bit-dac-tutorial/using-with-arduino
Adafruit_MCP4725 dac;

/**************************************************************************/
// constants won't change. Used here to set a pin number:
const int ledPin =  LED_BUILTIN;// the number of the LED pin

// Variables will change:
int ledState = LOW;             // ledState used to set the LED

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time values updated

// constants won't change:
const long interval = 1000;           // interval (milliseconds)
                                      // 0.03125Hz = 
/**************************************************************************/
//3 bits to address 8 ch analog mux configured as 8 in to 1 out:
  // ch1 = MCP4725 dac @ I2C addr. 0x60
  // ch0 = panel trim pot
const int uiMuxAddr0 = 7;
const int uiMuxAddr1 = 6;
const int uiMuxAddr2 = 5;
/**************************************************************************/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Hello!");
  Serial.println("Generating square wave @ 0.5Hz w/50% duty cylce!");
  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  // For MCP4725A0 the address is 0x60 or 0x61
  // For MCP4725A2 the address is 0x64 or 0x65
  dac.begin(0x61); //Address of our DAC module
/**************************************************************************/
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
/**************************************************************************/
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(uiMuxAddr0, OUTPUT);
  pinMode(uiMuxAddr1, OUTPUT);
  pinMode(uiMuxAddr2, OUTPUT);  
    digitalWrite(uiMuxAddr0, HIGH);
    digitalWrite(uiMuxAddr1, LOW);
    digitalWrite(uiMuxAddr2, LOW);
/**************************************************************************/
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t i;
  unsigned long currentMillis = millis();

      for (i = 0; i < 32; i++)
      {
        if (currentMillis - previousMillis >= interval) {
          // save the last time you blinked the LED
          previousMillis = currentMillis;
          dac.setVoltage(2048, false);
          // toggle LED state
          if (ledState == LOW) {
            ledState = HIGH;
          } else {
            ledState = LOW;
          }            
          // Change LED pin and mux address MSB via ledState variable:
          digitalWrite(ledPin, ledState);
          digitalWrite(uiMuxAddr0, ledState);
        }    
      }
}

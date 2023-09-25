/*
ESPboyMCP class
for www.ESPboy.com project by RomanS
https://hackaday.io/project/164830-espboy-games-iot-stem-for-education-fun
v1.0
*/

#ifndef ESPboy_MCP
#define ESPboy_MCP

#include <Arduino.h>
#include <Wire.h>


#define MCP23017address 0x20 // actually it's 0x20 but in <Adafruit_MCP23017.h> lib there is (x|0x20) :)
#define MCP4725address  0x60

class ESPboyMCP{

public:
  void begin();
  uint8_t setDAC(const uint16_t value, uint8_t reg);
  uint8_t readRegister(uint8_t addr);
  void writeRegister(uint8_t regAddr, uint8_t regValue);
  void updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr);
  void pinMode(uint8_t p, uint8_t d);
  void pullUp(uint8_t p, uint8_t d);
  void digitalWrite(uint8_t pin, uint8_t d);
  uint16_t readGPIOAB();
};

#endif

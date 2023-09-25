/*
ESPboyMCP class
for www.ESPboy.com project by RomanS
https://hackaday.io/project/164830-espboy-games-iot-stem-for-education-fun
v1.0
*/


void ESPboyMCP::begin() {
	Wire.begin();
    Wire.setClock(400000);
	writeRegister(0x00,0xff);
	writeRegister(0x01,0xff);
}


uint8_t ESPboyMCP::setDAC(const uint16_t value, uint8_t reg) {
  uint8_t h = (value / 16);
  uint8_t l = (value & 0x0F) << 4;
  Wire.beginTransmission(MCP4725address);
  reg;
  Wire.write(reg);
  Wire.write(h);
  Wire.write(l);
  return Wire.endTransmission();
}


uint8_t ESPboyMCP::readRegister(uint8_t addr){
	Wire.beginTransmission(MCP23017address);
	Wire.write(addr);
	Wire.endTransmission();
	Wire.requestFrom(MCP23017address, 1);
	return Wire.read();
}

void ESPboyMCP::writeRegister(uint8_t regAddr, uint8_t regValue){
	// Write the register
	Wire.beginTransmission(MCP23017address);
	Wire.write(regAddr);
	Wire.write(regValue);
	Wire.endTransmission();
}

void ESPboyMCP::updateRegisterBit(uint8_t pin, uint8_t pValue, uint8_t portAaddr, uint8_t portBaddr){
	uint8_t regValue;
	uint8_t regAddr=(pin<8)?portAaddr:portBaddr;
	uint8_t bit=pin%8;
	regValue = readRegister(regAddr);
	bitWrite(regValue,bit,pValue);
	writeRegister(regAddr,regValue);
}

void ESPboyMCP::pinMode(uint8_t p, uint8_t d) {
	updateRegisterBit(p,(d==INPUT),0x00,0x01);
}

void ESPboyMCP::pullUp(uint8_t p, uint8_t d) {
	updateRegisterBit(p,d,0x0C,0x0D);
}

void ESPboyMCP::digitalWrite(uint8_t pin, uint8_t d) {
	uint8_t gpio;
	uint8_t bit=pin%8;
	uint8_t regAddr=(pin<8)?0x14:0x15;
	gpio = readRegister(regAddr);
	bitWrite(gpio,bit,d);
	regAddr=(pin<8)?0x12:0x13;
	writeRegister(regAddr,gpio);
}

uint16_t ESPboyMCP::readGPIOAB() {
	uint16_t ba = 0;
	uint8_t a;
	Wire.beginTransmission(MCP23017address);
	Wire.write(0x12);
	Wire.endTransmission();
	Wire.requestFrom(MCP23017address, 2);
	a = Wire.read();
	ba = Wire.read();
	ba <<= 8;
	ba |= a;
	return ba;
}

#include <Adafruit_NeoPixel.h> //to control RGB LED
#include <Adafruit_MCP23017.h> //to control buttons
#include <Adafruit_MCP4725.h>  //to control the LCD display backlit
#include <TFT_eSPI.h>          //to draw at LCD TFT
#include <ESP8266WiFi.h>       //to control WiFi

#include "ESPboyLogo.h"

#define LEDquantity     1
#define MCP23017address 0 // actually it's 0x20 but in <Adafruit_MCP23017.h> lib there is (x|0x20) :)
#define MCP4725address  0x60

//PINS
#define LEDPIN         D4
#define SOUNDPIN       D3
#define LEDLOCK        9
#define CSTFTPIN       8 //Chip Select pin for LCD (it's on the MCP23017 GPIO expander GPIO8)

#define PAD_LEFT        0x01
#define PAD_UP          0x02
#define PAD_DOWN        0x04
#define PAD_RIGHT       0x08
#define PAD_ACT         0x10
#define PAD_ESC         0x20
#define PAD_LFT         0x40
#define PAD_RGT         0x80
#define PAD_ANY         0xff


Adafruit_MCP23017 mcp;
Adafruit_MCP4725 dac;
TFT_eSPI tft;
Adafruit_NeoPixel pixels(LEDquantity, LEDPIN);


void setup(){
  Serial.begin(115200); //serial init
  WiFi.mode(WIFI_OFF); // to safe some battery power

//DAC init and backlit off
  dac.begin(MCP4725address);
  delay (100);
  dac.setVoltage(0, false);

//mcp23017 init for buttons, LED LOCK and TFT Chip Select pins
  mcp.begin(MCP23017address);
  delay(100);
  
  for (int i=0;i<8;i++){  
     mcp.pinMode(i, INPUT);
     mcp.pullUp(i, HIGH);}

//LED init
  mcp.pinMode(LEDLOCK, OUTPUT);
  mcp.digitalWrite(LEDLOCK, HIGH); 
  pinMode(LEDPIN, OUTPUT);
  pixels.begin();
  delay(10);
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.show();

//sound init and test
  pinMode(SOUNDPIN, OUTPUT);
  tone(SOUNDPIN, 200, 100); 
  delay(100);
  tone(SOUNDPIN, 100, 100);
  delay(100);
  noTone(SOUNDPIN);
  
//LCD TFT init
  mcp.pinMode(CSTFTPIN, OUTPUT);
  mcp.digitalWrite(CSTFTPIN, LOW);
  tft.begin();
  delay(100);
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

//draw ESPboylogo  
  tft.drawXBitmap(30, 24, ESPboyLogo, 68, 64, TFT_YELLOW);
  tft.setTextSize(1);
  tft.setTextColor(TFT_YELLOW);
  tft.setCursor(36,102);
  tft.print ("First test");

//LCD backlit fading on
  for (uint16_t bcklt=0; bcklt<4095; bcklt+=20){
    dac.setVoltage(bcklt, false);
    delay(10);}

//clear TFT and backlit on high
  dac.setVoltage(4095, false);
  tft.fillScreen(TFT_BLACK);
}


uint8_t getKeys() { return (~mcp.readGPIOAB() & 255); }


void loop(){ 
 uint8_t keypressed;
 uint8_t static rnd = 0;
 uint16_t static lcdbright = 700;
 
 keypressed=getKeys();

 if (keypressed){      
  
    if (rnd==0) {
      pixels.setPixelColor(0, pixels.Color(100, 0, 0)); 
      tft.setTextColor(TFT_RED);}
    if (rnd==1) {
      pixels.setPixelColor(0, pixels.Color(0, 100, 0)); 
      tft.setTextColor(TFT_GREEN); }
    if (rnd==2) {
      pixels.setPixelColor(0, pixels.Color(0, 0, 100)); 
      tft.setTextColor(TFT_BLUE); }
      
    tft.setCursor(0, 0);
    tft.setTextSize(2);
    
    tft.println("PRESSED:");
    if (keypressed&PAD_LEFT) tft.println("LEFT ");
    if (keypressed&PAD_RIGHT) tft.println("RIGHT");
    if (keypressed&PAD_UP) tft.println("UP   ");
    if (keypressed&PAD_DOWN) tft.println("DOWN ");
    if (keypressed&PAD_ACT) tft.println("ACT  ");
    if (keypressed&PAD_ESC) tft.println("ESC  ");
    if (keypressed&PAD_RGT) tft.println("RGT  ");
    if (keypressed&PAD_LFT) tft.println("LFT  ");
    
    tone(SOUNDPIN, keypressed*30);
    
    lcdbright += 30;    
    if (lcdbright > 1200) lcdbright = 400;
    dac.setVoltage(lcdbright, false);
 }
 
 else{ 
    rnd=random(0,3);
    noTone(SOUNDPIN);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); 
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.print("Millis: "); 
    tft.println(millis());
    tft.setCursor(0, 8);
    tft.print("TFT brt:"); 
    tft.print(lcdbright); 
 }
 
 pixels.show();
 delay(200);
 tft.fillScreen(TFT_BLACK);
}

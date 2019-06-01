#include <Adafruit_NeoPixel.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ST7735.h> 
#include <Adafruit_GFX.h> 
#include <U8x8lib.h>
#include <Wire.h>   
#include <ESP8266WiFi.h>
#include "ESPboyLogo.h"

#define LEDquantity     1
#define MCP23017address 0 // actually it's 0x20 but in <Adafruit_MCP23017.h> lib there is (x|0x20) :)
#define MCP4725dacresolution 8
#define MCP4725address 0

//PINS
#define LEDPIN         D4
#define SOUNDPIN       D3


//SPI for LCD
#define csTFTMCP23017pin 8
#define TFT_RST       -1
#define TFT_DC        D8
#define TFT_CS        -1

//FOR OLED
//U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE); 	      
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

Adafruit_MCP23017 mcp;
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_NeoPixel pixels(LEDquantity, LEDPIN);
Adafruit_MCP4725 dac;

void setup(){
  Serial.begin(115200); //serial init
  delay (100);
  WiFi.mode(WIFI_OFF); // to safe some battery power

//LED init
  pinMode(LEDPIN, OUTPUT);
  pixels.begin();
  delay (100);
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.show();

//buttons on mcp23017 init
  mcp.begin(MCP23017address);
  delay (100);
  for (int i=0;i<8;i++){  
     mcp.pinMode(i, INPUT);
     mcp.pullUp(i, HIGH);}

//TFT init     
  mcp.pinMode(csTFTMCP23017pin, OUTPUT);
  mcp.digitalWrite(csTFTMCP23017pin, LOW);
  tft.initR(INITR_144GREENTAB);
  delay (100);
  tft.setRotation(0);
  tft.fillScreen(ST77XX_BLACK);

//draw ESPboylogo  
  tft.drawXBitmap(30, 24, ESPboyLogo, 68, 64, ST77XX_YELLOW);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setCursor(36,102);
  tft.print ("First test");

//sound init and test
  pinMode(SOUNDPIN, OUTPUT);
  tone(SOUNDPIN, 200, 100); 
  delay(100);
  tone(SOUNDPIN, 100, 100);
  delay(100);
  noTone(SOUNDPIN);
  digitalWrite(SOUNDPIN, HIGH);

//OLED init
  u8x8.setFont(u8x8_font_chroma48medium8_r);  

//DAC init 
dac.begin(0x62);
delay (100);
dac.setVoltage(255, false);

//clear TFT
  delay(2000);
  tft.fillScreen(ST77XX_BLACK);
}


void loop(){ 
 int8_t countled;
 int8_t static rnd=0;
 u8x8.setCursor(0,0);
 countled=0;
 
 for (int i=0;i<8;i++){
    if(mcp.digitalRead(i))u8x8.print("-");
    else {
       u8x8.print("*");
       countled++;}
 }

 if (countled){
    if (rnd==0) {
      pixels.setPixelColor(0, pixels.Color(countled*20, 0, 0)); 
      tft.setTextColor(ST77XX_RED); 
      tft.fillRect(0,100,128,28,ST77XX_RED);}
    if (rnd==1) {
      pixels.setPixelColor(0, pixels.Color(0, countled*20, 0)); 
      tft.setTextColor(ST77XX_GREEN); 
      tft.fillRect(0,100,128,28,ST77XX_GREEN);}
    if (rnd==2) {
      pixels.setPixelColor(0, pixels.Color(0, 0, countled*20)); 
      tft.setTextColor(ST77XX_BLUE); 
      tft.fillRect(0,100,128,28,ST77XX_BLUE);}
    tft.fillRect(0,0,128,16,ST77XX_BLACK);
    tft.fillRect(0,64,16,16,ST77XX_BLACK);
    tft.setCursor(0, 50);
    tft.setTextSize(2);
    tft.println("PRESSED");
    tft.fillRect(0,64,16,16,ST77XX_BLACK);
    tft.println(countled);
    tone(SOUNDPIN, countled*150);}
 else{ 
    rnd=random(0,3);
    noTone(SOUNDPIN);
    digitalWrite(SOUNDPIN, HIGH);
    pixels.setPixelColor(0, pixels.Color(0, 0, 0)); 
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.print("Millis: "); 
    tft.fillRect(40,0,70,8,ST77XX_BLACK);
    tft.fillRect(0,48,120,32,ST77XX_BLACK);
    tft.println(millis());
 }
 pixels.show();
 delay(100);
}

/*
Try "First test" to check your ESPboy hardware and start coding!
In this example we are using standard Adafruit Arduino IDE libraries

www.espboy.com project by RomanS - roman.sokolov@gmail.com (C) 2023

Preliminary actions:
- Install Arduino IDE https://www.arduino.cc/en/Main/Software
- Install the WeMos D1 mini ESP866 board to your Arduino IDE https://www.instructables.com/Wemos-ESP8266-Getting-Started-Guide-Wemos-101/
- Install all the libs for ESPboy from here https://github.com/ESPboy-edu/ESPboy_ArduinoIDE_Libraries
- Select the "LOLIN(WEMOS) D1 R2 & mini" board in the Arduino IDE and compile this code

Test ESPboy hardware:
- Power on
- 8 buttons
- Display TFT and its backlit
- RGB led
- Buzzer/Speaker

Have fun :)

*/


#include <Arduino.h>
#include <ESP8266WiFi.h>       //WiFi controll
#include <Adafruit_GFX.h>      //Core graphics library
#include <Adafruit_ST7735.h>   //Display ST7735
#include <Adafruit_NeoPixel.h> //RGB LED 
#include <Adafruit_MCP4725.h>  //DAC backlti LCD control
#include <Adafruit_MCP23017.h> //GPIO extender (buttons and more)

#include <FS.h> 
using fs::FS;

#define TFT_CS         -1
#define TFT_RST        -1                                            
#define TFT_DC         16
  
#define MCP23017address 0 // actually it's 0x20 but in <Adafruit_MCP23017.h> lib there is (x|0x20) :)
#define MCP4725address 0x60

#define LEDPIN         D4
#define SOUNDPIN       D3
#define LEDLOCK        9
#define CSTFTPIN       8 

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
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_NeoPixel led(1, LEDPIN, NEO_GRB + NEO_KHZ800);


const uint8_t ESPboyLogo[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 
  0x01, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0xFC, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x83, 0x1F, 0xFC, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xD0, 0xC3, 0x3F, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 
  0xE3, 0x7F, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE1, 0x7F, 0x78, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x7F, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xA0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xA0, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x7F, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x41, 0x3E, 0x78, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xF0, 0x83, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
  0x03, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x03, 0x00, 0xF4, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xB0, 0x03, 0x0F, 0xEC, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0x81, 0x1F, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x80, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1E, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1D, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0x01, 0x0F, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 
  0x03, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0xFC, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xD0, 0x03, 0x0F, 0xF4, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xB0, 0x83, 0x1F, 0xEC, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 
  0x81, 0x1F, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1E, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x1D, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x1E, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x0F, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0x0F, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3D, 0x40, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x3B, 0xC0, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E, 0x80, 0x07, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x07, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 
  0x0F, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x0F, 0x00, 0x7E, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x0F, 0x00, 0x7A, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xC0, 0x0E, 0x00, 0x76, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x07, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xE0, 0xE7, 0xF7, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF7, 
  0xF7, 0x37, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x30, 0x30, 0xF6, 0xF1, 
  0xCC, 0x00, 0x00, 0x00, 0xE0, 0xF3, 0x31, 0xF6, 0xFB, 0xCD, 0x00, 0x00, 
  0x00, 0xE0, 0xE3, 0xF3, 0x37, 0x9B, 0xCD, 0x00, 0x00, 0x00, 0xE0, 0xC0, 
  0xF7, 0x33, 0x9B, 0xCD, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x36, 0x30, 0x9B, 
  0xCD, 0x00, 0x00, 0x00, 0xE0, 0xF7, 0x37, 0xF0, 0xFB, 0xFD, 0x00, 0x00, 
  0x00, 0xE0, 0xF7, 0x33, 0xF0, 0xF1, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 
};


uint8_t ESPboyGetKeys() { return (~mcp.readGPIOAB() & 255); }

int8_t isDAC;

void setup() {
  Serial.begin(115200); //serial init
  WiFi.mode(WIFI_OFF); // to safe battery power

//DAC backlit LCD control init
  dac.begin(MCP4725address);
  delay (100);
  dac.setVoltage(0, false); //LCD backlit off

//mcp23017 init
  mcp.begin(MCP23017address);
  
//buttons init
  for (int i=0;i<8;i++){  
     mcp.pinMode(i, INPUT);
     mcp.pullUp(i, HIGH);}
     
//LED init
  pinMode(LEDPIN, OUTPUT);
  mcp.pinMode(LEDLOCK, OUTPUT);
  mcp.digitalWrite(LEDLOCK, HIGH); 
  led.begin();
  led.clear();
  led.show();
  
//sound init
  pinMode(SOUNDPIN, OUTPUT);

//display init
  mcp.pinMode(CSTFTPIN, OUTPUT);
  mcp.digitalWrite(CSTFTPIN, LOW);
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  
//draw logo
  tft.drawXBitmap(30, 24, ESPboyLogo, 68, 64, ST77XX_YELLOW);
  const char toPrint[] = {"First test"};
  tft.setCursor((128-(strlen(toPrint)*6))/2, 102);
  tft.setTextColor(ST77XX_YELLOW);
  tft.print(toPrint);
  
//LCD backlit fading on
  for (uint16_t bcklt=300; bcklt<2500; bcklt+=30){
    dac.setVoltage(bcklt, false);
    delay(10);}
    
  isDAC = dac.setVoltage(4095, false);  //set max LCD backlit
  tft.fillScreen(ST77XX_BLACK); //clear display
}



void loop(){ 
 static uint8_t keypressed;
 static uint8_t rnd;
 static uint16_t lcdbright = 4095;
 
 keypressed=ESPboyGetKeys();

 if (keypressed){      
    if (rnd==0) {
      led.setPixelColor(0, led.Color(50, 0, 0));
      tft.setTextColor(ST77XX_RED);}
    if (rnd==1) {
      led.setPixelColor(0, led.Color(0, 50, 0)); 
      tft.setTextColor(ST77XX_GREEN); }
    if (rnd==2) {
      led.setPixelColor(0, led.Color(0, 0, 50));
      tft.setTextColor(ST77XX_BLUE); }
      
    tft.setCursor(0, 0);
    tft.setTextSize(2);
 
    tft.println("PRESSED:");
    if (keypressed&PAD_LEFT)  tft.println("LEFT ");
    if (keypressed&PAD_RIGHT) tft.println("RIGHT");
    if (keypressed&PAD_UP)    tft.println("UP   ");
    if (keypressed&PAD_DOWN)  tft.println("DOWN ");
    if (keypressed&PAD_ACT)   tft.println("ACT  ");
    if (keypressed&PAD_ESC)   tft.println("ESC  ");
    if (keypressed&PAD_RGT)   tft.println("RGT  ");
    if (keypressed&PAD_LFT)   tft.println("LFT  ");
    
    tone(SOUNDPIN,keypressed*30);

    lcdbright += 100;    
    if (lcdbright > 4000) lcdbright = 500;
    isDAC = dac.setVoltage(lcdbright, false);
    tft.setTextSize(1);
    tft.print("TFT brt:"); 
    if (isDAC) tft.println(lcdbright); 
    else tft.println(" NO DAC"); 
 }

 else{ 
    rnd = random(0,3);
    noTone(SOUNDPIN);
    led.clear();
    tft.setCursor(0, 0);
    tft.setTextSize(1);
    tft.print("Millis: "); 
    tft.println(millis());
    tft.setCursor(0, 8);
    tft.print("TFT brt:"); 
    if (isDAC) tft.println(lcdbright); 
    else tft.println(" NO DAC"); 
}

 led.show(); 
 digitalWrite(2,HIGH);
 delay(200);
 tft.fillScreen(ST77XX_BLACK);
}

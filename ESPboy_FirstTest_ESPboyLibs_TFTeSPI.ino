/*
Try "First test" to check your ESPboy hardware and start coding!
In this example we are using original ESPboy Arduino IDE libraries

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

IMPORTANT! 
if you are using/updating original TFTeSPI library
you have to edit or replace usersetup.h file in the TFTeSPI folder in your Arduino libraries collection 
according to this https://github.com/ESPboy-edu/ESPboy_ArduinoIDE_Libraries/blob/master/TFT_eSPI-master/User_Setup.h
*/


#include "lib/ESPboyInit.h"
#include "lib/ESPboyInit.cpp"

ESPboyInit myESPboy;
int8_t isDAC;

void setup(){
  myESPboy.begin("First test");
  isDAC = myESPboy.mcp.writeDAC(4096, false);
}


void loop(){ 
 static uint8_t keypressed;
 static uint8_t rnd;
 static uint16_t lcdbright = 4095;
 
 keypressed=myESPboy.getKeys();

 if (keypressed){      
    if (rnd==0) {
      myESPboy.myLED.setRGB(100, 0, 0); 
      myESPboy.tft.setTextColor(TFT_RED);}
    if (rnd==1) {
      myESPboy.myLED.setRGB(0, 100, 0); 
      myESPboy.tft.setTextColor(TFT_GREEN); }
    if (rnd==2) {
      myESPboy.myLED.setRGB(0, 0, 100); 
      myESPboy.tft.setTextColor(TFT_BLUE); }
      
    myESPboy.tft.setCursor(0, 0);
    myESPboy.tft.setTextSize(2);
 
    myESPboy.tft.println("PRESSED:");
    if (keypressed&PAD_LEFT) myESPboy.tft.println("LEFT ");
    if (keypressed&PAD_RIGHT) myESPboy.tft.println("RIGHT");
    if (keypressed&PAD_UP) myESPboy.tft.println("UP   ");
    if (keypressed&PAD_DOWN) myESPboy.tft.println("DOWN ");
    if (keypressed&PAD_ACT) myESPboy.tft.println("ACT  ");
    if (keypressed&PAD_ESC) myESPboy.tft.println("ESC  ");
    if (keypressed&PAD_RGT) myESPboy.tft.println("RGT  ");
    if (keypressed&PAD_LFT) myESPboy.tft.println("LFT  ");
    
    myESPboy.playTone(keypressed*30);
    
    lcdbright += 100;    
    if (lcdbright > 4000) lcdbright = 500;
    isDAC = myESPboy.mcp.writeDAC(lcdbright, false);
    myESPboy.tft.setTextSize(1);
    myESPboy.tft.print("TFT brt:"); 
    if (isDAC) myESPboy.tft.println(lcdbright); 
    else myESPboy.tft.println(" NO DAC"); 
 }
 
 else{ 
    rnd=random(0,3);
    myESPboy.noPlayTone();
    myESPboy.myLED.setRGB(0, 0, 0); 
    myESPboy.tft.setCursor(0, 0);
    myESPboy.tft.setTextSize(1);
    myESPboy.tft.print("Millis: "); 
    myESPboy.tft.println(millis());
    myESPboy.tft.print("TFT brt:"); 
    if (isDAC) myESPboy.tft.println(lcdbright); 
    else myESPboy.tft.println(" NO DAC"); 
 }
 
 delay(200);
 myESPboy.tft.fillScreen(TFT_BLACK);
}

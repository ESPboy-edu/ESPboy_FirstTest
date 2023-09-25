/*
ESPboyOTA2 class AppStore (OTA2) v6.0
www.ESPboy.com
Proprietary license 2021 (C) RomanS espboy.edu@gmail.com


Features:
1. To become registered user and to increase Access Level fill "ESPboy AppStore registration form"
https://forms.gle/1ZZUgR7N8Mxhgnp17

2. Keep pressed A or B during reset to connect ESPboy App Store
  - A for attemp to connect last known WiFi
  - B to scan available WiFi's
3. There are two modes in OTA: keyboard and console
4. To switch modes use RGT+LGT or A+B
5. In keyboard mode
  - LEFT+UP - switch on caps lock
  - RGT or LFT scroll console window up/down
  - UP/DOWN/LEFT/RIGHT to chose char
  - short press A - enter char to typing string
  - long press A - finish entering, finish typing
  - short press B - delete last char in typing string
  - long press B - delete typing string
6. In console mode
  - UP/DOWN, RGT/LFT, LEFT/RIGHT - scroll console window
  - B - switch to keyboard mode
7. For registered users mark "!" shows new files added from your last visit
8. Mark "-" indicates that you have not enough Access level points to load App
9. Registered users can set Likes for Apps (just one per user per app)


Check "ESPboyGUI.h" for defines:
  - #define U8g2 - if defined then using font 4x6, if commented using font 6x8
  - #define buttonclicks - if defined - button are clicking but it takes more than 1kb RAM, if commented - no clicks and more free RAM

*/


#include "lib/ESPboyInit.h"
#include "lib/ESPboyInit.cpp"

ESPboyInit myESPboy;

uint16_t lcdbright = 4095;

void setup(){
  myESPboy.begin("First test");
}


void loop(){ 
 uint8_t keypressed;
 static uint8_t rnd = 0;
 
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
    if (lcdbright > 4095) lcdbright = 3000;
    myESPboy.dac.setVoltage(lcdbright, false);
 }
 
 else{ 
    rnd=random(0,3);
    myESPboy.noPlayTone();
    myESPboy.myLED.setRGB(0, 0, 0); 
    myESPboy.tft.setCursor(0, 0);
    myESPboy.tft.setTextSize(1);
    myESPboy.tft.print("Millis: "); 
    myESPboy.tft.println(millis());
    myESPboy.tft.setCursor(0, 8);
    myESPboy.tft.print("TFT brt:"); 
    myESPboy.tft.print(lcdbright); 
    myESPboy.dac.setVoltage(4095, false);
 }
 
 delay(200);
 myESPboy.tft.fillScreen(TFT_BLACK);
}

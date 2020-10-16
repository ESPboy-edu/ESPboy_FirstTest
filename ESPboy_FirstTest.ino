#include "ESPboyInit.h"
#include "ESPboyLED.h"

ESPboyInit myESPboy;
ESPboyLED myLED;

void setup(){
  myESPboy.begin("First test");
  myLED.begin();
}


void loop(){ 
 uint8_t keypressed;
 static uint8_t rnd = 0;
 static uint16_t lcdbright = 700;
 
 keypressed=myESPboy.getKeys();

 if (keypressed){      
  
    if (rnd==0) {
      myLED.setRGB(100, 0, 0); 
      myESPboy.tft.setTextColor(TFT_RED);}
    if (rnd==1) {
      myLED.setRGB(0, 100, 0); 
      myESPboy.tft.setTextColor(TFT_GREEN); }
    if (rnd==2) {
      myLED.setRGB(0, 0, 100); 
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
    
    lcdbright += 30;    
    if (lcdbright > 700) lcdbright = 400;
    myESPboy.dac.setVoltage(lcdbright, false);
 }
 
 else{ 
    rnd=random(0,3);
    myESPboy.noPlayTone();
    myLED.setRGB(0, 0, 0); 
    myESPboy.tft.setCursor(0, 0);
    myESPboy.tft.setTextSize(1);
    myESPboy.tft.print("Millis: "); 
    myESPboy.tft.println(millis());
    myESPboy.tft.setCursor(0, 8);
    myESPboy.tft.print("TFT brt:"); 
    myESPboy.tft.print(lcdbright); 
 }
 
 delay(200);
 myESPboy.tft.fillScreen(TFT_BLACK);
}

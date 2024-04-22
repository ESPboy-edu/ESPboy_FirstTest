# Try "First test" to check your ESPboy after assembling
www.espboy.com project

There are 3 versions:

1. ESPboy_FristTest_AdafruitLibs - uses only standard Adafruit libraries to control ESPboy hardware (LED, buttons, sound, display)

2. ESPboy_FirstTest_ESPboyLibs_TFTeSPI -- uses ESPboy libs and [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI?ysclid=ln67tav62z348840877) graphics library for display (be carefull, to force it work properly with ESPboy's display you have to edit parameters in "User_Setup.h" file in TFT_eSPI library folder according [to this](https://github.com/ESPboy-edu/ESPboy_ArduinoIDE_Libraries/blob/master/TFT_eSPI-master/User_Setup.h) )

3. ESPboy_FirstTest_ESPboyLibs_LovyanGFX -- uses ESPboy libs and [LovyanGFX](https://github.com/lovyan03/LovyanGFX) graphics library for display

4. ESPboy_ArdublockFirstTest -- uses [Ardublock.ru v3](http://ardublock.ru/3/)

# To start work with ESPboy

1. Install Arduino IDE legacy 1.8.n recommended (not v2.n IDE) https://www.arduino.cc/en/Main/Software

2. Install the WeMos D1 mini ESP866 board to your Arduino IDE https://www.instructables.com/Wemos-ESP8266-Getting-Started-Guide-Wemos-101/

3. Install all the libs for ESPboy from here https://github.com/ESPboy-edu/ESPboy_ArduinoIDE_Libraries

4. Select the "LOLIN(WEMOS) D1 R2 & mini" board in the Arduino IDE and compile this code

5. Test ESPboy hardware:
- Power on
- 8 buttons
- Display TFT and its backlit
- RGB led
- Buzzer/Speaker

6. Have fun :)

7. For better experience you have to istall to your Arduino IDE ["Little FS file uploader plugin"](https://github.com/earlephilhower/arduino-esp8266littlefs-plugin) and ["ESP exception decoder plugin"](https://github.com/me-no-dev/EspExceptionDecoder)

8. If you want to have professinal development tool much more powerfull than standard Arduino IDE, learn ["VS Code" + "PlatformIO"](https://circuitsgeek.com/guides-and-how-to/programming-esp8266-using-vs-code-and-platformio/)

9. [Use recommended Arduino IDE settings](https://github.com/ESPboy-edu/ESPboy_FirstTest/blob/master/settings.png)

![Arduino IDE settings](settings.png)



# Try "First test" to start programming

1. Use this example to start coding with ESPboy

2. To init use begin() of ESPboy_Init class https://github.com/ESPboy-edu/ESPboy_Classes 

3. For doing graphics use methods of TFT_eSPI class https://github.com/Bodmer/TFT_eSPI or adafruit ST7735 lib https://github.com/adafruit/Adafruit-ST7735-Library  or LovyanGFX lib https://github.com/lovyan03/LovyanGFX

4. For buttons use getkeys() of ESPboyInit and keypressed&PAD_LEFT, keypressed&PAD_RIGHT and so on to understand what key is exactly pressed

5. For LED use ESPboy_LED class https://github.com/ESPboy-edu/ESPboy_Classes or NeoPixel https://github.com/adafruit/Adafruit_NeoPixel

6. For sound use playTone(frequency, duration), playTone (frequency) and noPlayTone() methods of ESPboy_Init class https://github.com/ESPboy-edu/ESPboy_Classes 

7. To control the LCD backlit use Adafruit MCP4725 library methods https://github.com/adafruit/Adafruit_MCP4725 

8. To upload data (files) to internal flash file system use Arduino IDE plugins: 

a) Little FS -  https://github.com/earlephilhower/arduino-esp8266littlefs-plugin

b) SPIFFS - https://github.com/esp8266/arduino-esp8266fs-plugin

9. To upload to ESPboy already compiled ".bin" files, use [Flash Download Tools](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32)

10. Use ESP8266 Arduino Core documentation https://arduino-esp8266.readthedocs.io/en/latest/index.html

11. Ask questions in ESPboy forum https://community.arduboy.com and ESPboy discord chat https://discord.gg/kMWhY2x

12. Have FUN! )

Regards,
Roman
//


MIT License

Copyright (c) 2020 ESPboy

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

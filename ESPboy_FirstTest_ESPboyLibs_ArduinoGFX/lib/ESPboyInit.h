/*
ESPboy_Init class
for www.ESPboy.com project by RomanS
https://hackaday.io/project/164830-espboy-games-iot-stem-for-education-fun
v1.0
*/

#ifndef ESPboy_Init
#define ESPboy_Init

#include <Arduino.h>
#include "ESPboyMCP.h"
#include "ESPboyMCP.cpp"
#include "ESPboyLED.h"
#include "ESPboyLED.cpp"
#include "ESPboylogo.h"

#include <Arduino_GFX_Library.h>

#include <ESP8266WiFi.h>       //to control WiFi

#include <FS.h> 
using fs::FS;

#define TFT_CS         -1
#define TFT_RST        -1                                            
#define TFT_DC         16

#define MCP4725address  0x60
#define CSTFTPIN 		8  //Chip Select pin for LCD (it's on the MCP23017 GPIO expander GPIO8)

#define LEDPIN         D4
#define SOUNDPIN       D3

#define PAD_LEFT        0x01
#define PAD_UP          0x02
#define PAD_DOWN        0x04
#define PAD_RIGHT       0x08
#define PAD_ACT         0x10
#define PAD_ESC         0x20
#define PAD_LFT         0x40
#define PAD_RGT         0x80
#define PAD_ANY         0xff

// Default color definitions
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
#define TFT_SILVER      0xC618      /* 192, 192, 192 */
#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
#define TFT_VIOLET      0x915C      /* 180,  46, 226 */


class ESPboyInit{

public:
  ESPboyMCP mcp;
  Arduino_DataBus *bus;
  Arduino_GFX *tft;
  ESPboyLED myLED;


  ESPboyInit();
  void begin(const char *appName);
  
  uint8_t getKeys();
  void playTone(uint16_t frq, uint16_t dur);
  void playTone(uint16_t frq);
  void noPlayTone();
};

#endif

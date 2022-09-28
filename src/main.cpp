//---------------------------------------------------------------------------------
//
// Derived from:  Arduino LED Tutorial - (c) 2020 Dave Plummer, All Rights Reserved.
//
//  File:         RGB_LED_esp32dev/main.cpp          Creator(s): Dave Plummer
//                                                               TW-NewbRangerTom
//
//  Description:
//    Draw sample effects on an addressable RGB LED strip using
//    the EZSBC ESP32_ANT_1 Breakout and Developement Board.  https://www.ezsbc.com/product/wifi01u/
// 
//  History:      Feb-7-2022    TW-NewbRangerTom        Copied for personal use and learning
//                Feb-22-2022   TW-NewbRangerTom        refactored with EVERY_N_MILLISECONDS
//                                                      refactored comet using beat timers
//                Mar-03-2022   TW-NewbRangerTom        Removed OLED, refactored for esp32dev board
//                Apr-07-2022   TW-NewbRangerTom        Added Bluetooth
//                                                      moved to ledgfx.h: 
//                                                        #define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
//                                                        #define TIMES_PER_SECOND(x) EVERY_N_MILLISECONDS(1000 / x)
//                Apr-11-2022   TW-NewbRangerTom        Added PurpleRainEffect
//                Apr-25-2022   TW-NewbRangerTom        Updated README.md
//                                                      Added color_palette.txt with code to add to FastLED/colorutils
//                Sep-28-2022   TW-NewbRangerTom        Cleaned up a few dependency issues in some of the functions.
// 
// !!! CAUTION:
//    1. Some patterns require more power to run properly. Ensure you do not set power limit higher than power supply is rated.
//
//---------------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
// #include "BluetoothSerial.h"

// potentiometer
#define POT_PIN             27
int potVal = analogRead(POT_PIN);

// For FastLED
#define CHIPSET             WS2812B     // specify the chipset of the led strip
#define COLOR_ORDER         GRB         // specify the rgb order (not all chipsets have the same order) 
#define STRIP1_LEDS         144         // number of LEDs on strip 1
#define UF_LEDS             72          // number of LEDs for each half of Ukrain Flag
#define LED_PIN             23
#define LED_BUILTIN         16          // builtin RGB LED1 Red pin

CRGB h_LEDs[STRIP1_LEDS] = {0};         // Frame buffer for FastLED

int h_Brightness         =  map(potVal, 0, 1023, 0, 255);
int h_Brightness         =  96;         //  brightness range 0 - 255  !!! CAUTION: setting to 255 could have negative effects if underpowered
int h_PowerLimit         =  15000;      //  1000mW = 1W Power Limit   !!! SEE CAUTION IN HEADER BLOCK. I have started using a 5V-10A-50W power supply.

uint8_t initialHue       =  0;
const uint8_t deltaHue   =  16;
const uint8_t hueDensity =  4;

// LED effect headers - User defined headers
#include "ledgfx.h"
#include "bounce.h"
#include "comet.h"      // *See caution # 1.
#include "fire.h"
#include "marquee.h"    // *See caution # 1.
#include "static.h"
#include "twinkle.h"    // *See caution # 1.

// ----- Class Constructors
BouncingBallEffect balls(STRIP1_LEDS, 8, 32, true);                  // Bouncing Ball Effect (length, count, fade, mirrored)
IceFireEffect      ice(STRIP1_LEDS, 15, 100, 3, 4, true, true);      // FireEffect, IceFireEffect, and PurpleRainEffect
FireEffect         fire(STRIP1_LEDS, 15, 100, 3, 4, true, true);     // reversed and bmirrored true/false combinations:
PurpleRainEffect   rain(STRIP1_LEDS, 15, 100, 3, 4, true, true);     // f-f = end -> 0 : t-f = 0 -> end : f-t = center -> out : t-t = ends -> center
// BluetoothSerial ESP_BT;

// --- User defined function(s) or function prototype(s) -------------------------

void Bounce(){
  FastLED.clear();
  balls.Draw();
  FastLED.setBrightness(h_Brightness);
};

void Marquee(int NUM_LEDS){
  EVERY_N_MILLISECONDS(20){ DrawMarquee(NUM_LEDS); };
};

void MyFire(){
  FastLED.clear();
  fire.DrawFire();
  FastLED.setBrightness(h_Brightness);
};

void MyIceFire(){
  FastLED.clear();
  ice.DrawIceFire();
  FastLED.setBrightness(h_Brightness);
};

void PurpleR(){
  FastLED.clear();
  rain.DrawPurpleRain();
  FastLED.setBrightness(h_Brightness);
};

void Rainbow(int NUM_LEDS){
  fill_rainbow(h_LEDs, NUM_LEDS, initialHue += hueDensity, deltaHue);
};

// -------------------------------------------------

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);                                           //  Builtin LED mode declaration
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  // ESP_BT.begin("32db_LED_Light_Show");
  while (!Serial){}
  Serial.println("ESP32 Startup");

  FastLED.addLeds< CHIPSET, LED_PIN, COLOR_ORDER >(h_LEDs, STRIP1_LEDS);               //  Add our LED strip to the FastLED library
  FastLED.setBrightness(h_Brightness);
  set_max_power_indicator_LED(LED_BUILTIN);                               //  Light the builtin LED if we power throttle
  FastLED.setMaxPowerInMilliWatts(h_PowerLimit);                          //  Set the power limit, above which brightness will be throttled
  FastLED.clear();

}

void loop() {

  while (true){
    
    // byte btReadNew = ESP_BT.read();

    // LED strip patern functions
    // uncomment the effect to use

    // clearLEDs();
    // Marquee(STRIP1_LEDS);                             // see annotations in marquee.h for options
    // DrawComet(STRIP1_LEDS);                           // 
    // DrawCometGfx(STRIP1_LEDS);                        //
    // DrawComet3(STRIP1_LEDS);                          //
    // Bounce();                              // Bouncing balls using BouncingBallEffect from bounce.h
    // DrawMarquee();                         // multi color scrolling marquee effect
    // fillGreen(STRIP1_LEDS);                           // DrawPixels color = CRGB::Green
    // DrawTwinkle();                         // multi color twinkle effect
    // DrawPurpleTwinkle();                   // purple color palette twinkle effect
    // Plaid();                               // solid fill color = CRGB::Plaid
    // Rainbow(STRIP1_LEDS);                             //
    // firstLED();                            // light LED 0 CRGB::Red
    // lightFullStrip();                      // solid fill color = CRGB::Red
    // MyFire();                              // red palette fire effect
    // MyIceFire();                           // blue palette fire effect
    // PurpleR();                             // purple palette fire effect
    // UkrainFlag();                          // 
  
    FastLED.setBrightness(h_Brightness);      // set brightness
    FastLED.delay(10);                        // Show and delay

  }

}  // end of void loop just in case you missed it.
//---------------------------------------------------------------------------------
//
//  Arduino LED Tutorial - (c) 2020 Dave Plummer, All Rights Reserved.
//
//  File:         RGB_LED_esp32dev/main.cpp
//
//  Description:
//    Draw sample effects on an addressable RGB LED strip and prints stats to
//    the OLED display on a Heltec ESP32 module.
// 
//  History:      Feb-7-2022    TW-NewbRanger        Copied for personal use and learning
//                Feb-22-2022   TW-NewbRanger        refactored with EVERY_N_MILLISECONDS
//                                                      refactored comet using beat timers
//                Mar-03-2022   TW-NewbRanger        Removed OLED, refactored for esp32dev board
//                Apr-07-2022   TW-NewbRanger        Added Bluetooth
//                                                   moved to ledgfx.h: 
//                                                      #define ARRAYSIZE(x) (sizeof(x) / sizeof(x[0]))
//                                                      #define TIMES_PER_SECOND(x) EVERY_N_MILLISECONDS(1000 / x)
//
//---------------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "BluetoothSerial.h"

BluetoothSerial ESP_BT;

// For FastLED
#define NUM_LEDS        144         // number of LEDs - using 60 out of 60
#define UF_LEDS         72          // number of LEDs for each half of Ukrain Flag
#define LED_PIN         23
#define LED_BUILTIN     16          // builtin RGB LED1 Red pin
CRGB h_LEDs[NUM_LEDS] = {0};        // Frame buffer for FastLED

int h_Brightness = 64;              //  brightness range 0 - 255  !!! CAUTION: setting to 255 could have negative effects if underpowered
int h_PowerLimit = 1500;            //  900mW Power Limit
int num_funcs   =  15;

// LED effect headers
#include "ledgfx.h"
#include "marquee.h"
#include "twinkle.h"
#include "comet.h"
#include "bounce.h"
#include "fire.h"
#include "static.h"

//  Bouncing Ball Effect
//
// (length, count, fade, mirrored)
// Creating instance of BouncingBallEffect called balls
BouncingBallEffect balls(NUM_LEDS, 8, 32, true);
IceFireEffect ice(NUM_LEDS, 15, 100, 3, 4, true, true);           // f-f = end -> 0 : t-f = 0 -> end : f-t = center -> out : t-t = ends -> center
FireEffect fire(NUM_LEDS, 30, 100, 3, 4, true, true);             // f-f = end -> 0 : t-f = 0 -> end : f-t = center -> out : t-t = ends -> center

void MyIceFire(){
    FastLED.clear();
    ice.DrawIceFire();
    FastLED.show(h_Brightness);
};

void MyFire(){
    FastLED.clear();
    fire.DrawFire();
    FastLED.show(h_Brightness);
};

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);                                           //  Builtin LED mode declaration
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(115200);
  ESP_BT.begin("32db_LED_Light_Show");
  while (!Serial){}
  Serial.println("ESP32 Startup");

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(h_LEDs, NUM_LEDS);               //  Add our LED strip to the FastLED library
  FastLED.setBrightness(h_Brightness);
  set_max_power_indicator_LED(LED_BUILTIN);                               //  Light the builtin LED if we power throttle
  FastLED.setMaxPowerInMilliWatts(h_PowerLimit);                          //  Set the power limit, above which brightness will be throttled
  FastLED.clear();

}

void loop() {

  uint8_t initialHue = 0;
  const uint8_t deltaHue = 16;
  const uint8_t hueDensity = 4;
  
  while (true){

  //----------------------------------------------------------------------------------------------------
      // LED strip patern functions
      // uncomment the effect to use

      // EVERY_N_MILLISECONDS(20){ DrawMarqueeComparison(); }  // see annotations in marquee.h for options
      // DrawComet();
      // DrawCometGfx();
      // DrawComet3();
      // balls.Draw();                                         //  Bouncing balls using BouncingBallEffect from bounce.h; comment out to use different effect
      // DrawMarquee();
      // DrawPixels(h_LEDs, NUM_LEDS, CRGB::Green);
      // DrawTwinkle();
      // fill_solid(h_LEDs, NUM_LEDS, CRGB::Green);
      // fill_rainbow(h_LEDs, NUM_LEDS, initialHue += hueDensity, deltaHue);
      // h_LEDs[0] = CRGB::Red;   // light LED 0
      // lightFullStrip();
      // MyFire();
      // MyIceFire();
      // UkrainFlag();


    // this system only works for the static (single iteration) functions.
      char btRead = ESP_BT.read();
      // for (int i = 0; i < num_funcs; i++) {
        if (btRead == 'a') DrawComet();                                         // dynamic
        if (btRead == 'b') DrawCometGfx();                                      // dynamic
        if (btRead == 'c') DrawComet3();                                        // dynamic
        if (btRead == 'd') balls.Draw();                                        // dynamic
        if (btRead == 'e') DrawMarquee();                                       // dynamic
        if (btRead == 'f') DrawPixels(h_LEDs[0], NUM_LEDS, CRGB::Green);        // static
        if (btRead == 'g') DrawTwinkle();                                       // dynamic
        if (btRead == 'h') fill_solid(h_LEDs, NUM_LEDS, CRGB::Green);           // static
        if (btRead == 'i') DrawTwinkleOne();                                    // dynamic
        if (btRead == 'j') h_LEDs[0] = CRGB::Red;                               // static
        if (btRead == 'k') lightFullStrip();                                    // static
        if (btRead == 'l') MyFire();                                            // dynamic
        if (btRead == 'm') MyIceFire();                                         // dynamic
        if (btRead == 'n') UkrainFlag();                                        // static
        if (btRead == 'o') FastLED.clear();                                     // sets all to HIGH / OFF / 0
      // }

  //----------------------------------------------------------------------------------------------------

    FastLED.setBrightness(h_Brightness);
    FastLED.delay(10);                                    // Show and delay

  }

}
//---------------------------------------------------------------------------------
//
// Derived from:  Arduino LED Tutorial - (c) 2020 Dave Plummer, All Rights Reserved.
//
//  File:         RGB_LED_esp32dev/main.cpp          Creator(s): Dave Plummer
//                                                               TW-NewbRanger
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
//                Apr-11-2022   TW-NewbRanger        Added PurpleRainEffect
// 
// !!! CAUTION:
//    1. Some patterns require more power to run properly. Ensure you do not set power limit higher than power supply is rated.
//
//---------------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "BluetoothSerial.h"

// For FastLED
#define NUM_LEDS           144         // number of LEDs - using 60 out of 60
#define UF_LEDS            72          // number of LEDs for each half of Ukrain Flag
#define LED_PIN            23
#define LED_BUILTIN        16          // builtin RGB LED1 Red pin

CRGB h_LEDs[NUM_LEDS]   = {0};         // Frame buffer for FastLED

int h_Brightness         = 96;         //  brightness range 0 - 255  !!! CAUTION: setting to 255 could have negative effects if underpowered
int h_PowerLimit         = 15000;      //  1000mW = 1W Power Limit   !!! SEE CAUTION IN HEADER BLOCK. I have started using a 5V-10A-50W power supply.
const int num_funcs      = 18;

uint8_t initialHue       = 0;
const uint8_t deltaHue   = 16;
const uint8_t hueDensity = 4;

// LED effect headers - User defined headers
#include "ledgfx.h"
#include "bounce.h"
#include "comet.h"      // *See caution # 1.
#include "fire.h"
#include "marquee.h"    // *See caution # 1.
#include "static.h"
#include "twinkle.h"    // *See caution # 1.

// ----- Class Constructors

BouncingBallEffect balls(NUM_LEDS, 8, 32, true);                  // Bouncing Ball Effect (length, count, fade, mirrored)
IceFireEffect ice(NUM_LEDS, 15, 100, 3, 4, true, true);           // FireEffect, IceFireEffect, and PurpleRainEffect
FireEffect fire(NUM_LEDS, 15, 100, 3, 4, true, true);             // reversed and bmirrored true/false combinations:
PurpleRainEffect rain(NUM_LEDS, 15, 100, 3, 4, true, true);       // f-f = end -> 0 : t-f = 0 -> end : f-t = center -> out : t-t = ends -> center
BluetoothSerial ESP_BT;


// --- User defined function prototypes -------------------------

void clearLEDs();
void firstLED();
void Marquee();
void MyFire();
void MyIceFire();
void nothingElseMatters();
void PurpleR();

// -------------------------------------------------

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

  while (true){

	//----------------------------------------------------------------------------------------------------
    // LED strip patern functions
    // uncomment the effect to use

    // Marquee();                                          // see annotations in marquee.h for options
    // DrawComet();
    // DrawCometGfx();
    // DrawComet3();
    // balls.Draw();                                       //  Bouncing balls using BouncingBallEffect from bounce.h; comment out to use different effect
    // DrawMarquee();
    // DrawPixels(h_LEDs, NUM_LEDS, CRGB::Green);
    // DrawTwinkle();
    // DrawPurpleTwinkle();
    // fill_solid(h_LEDs, NUM_LEDS, CRGB::Plaid);
    // fill_rainbow(h_LEDs, NUM_LEDS, initialHue += hueDensity, deltaHue);
    // h_LEDs[0] = CRGB::Red;   // light LED 0
    // lightFullStrip();
    // MyFire();
    // MyIceFire();
    PurpleR();
    // UkrainFlag();
    
    // if (ESP_BT.available()){
		// 	byte btRead = ESP_BT.read();
		// 	switch (btRead){
		// 		case 0:  clearLEDs(); break;
    //    case 1:	 DrawPixels(h_LEDs[0], NUM_LEDS, CRGB::Green);  break;
		// 		case 2:	 fill_solid(h_LEDs, NUM_LEDS, CRGB::Plaid);  break;
		// 		case 3:	 firstLED();  break;
		// 		case 4:	 lightFullStrip();  break;
		// 		case 5:	 UkrainFlag();  break;
		// 		case 6:	 fill_rainbow(h_LEDs, NUM_LEDS, initialHue += hueDensity, deltaHue);  break;
		// 		case 7:	 Marquee();  break;
		// 		case 8:	 balls.Draw();  break;
		// 		case 9:	 DrawComet();  break;
		// 		case 10: DrawCometGfx(); break;
		// 		case 11: DrawComet3(); break;
		// 		case 12: DrawTwinkle(); break;
		// 		case 13: DrawPurpleTwinkle(); break;
		// 		case 14: MyFire(); break;
		// 		case 15: MyIceFire(); break;
		// 		case 16: PurpleR(); break;
		// 		default: nothingElseMatters();
    //   }
    // }

  //----------------------------------------------------------------------------------------------------

  FastLED.setBrightness(h_Brightness);
  FastLED.delay(10);                                         // Show and delay

  }

}  // end of void loop just in case you missed it.

// --------------------------------------------------------------------
// 
// --- User defined functions
// 
// --------------------------------------------------------------------

void clearLEDs(){
  FastLED.clear();
};

void firstLED(){
  h_LEDs[0] = CRGB::Red;   // light LED 0
};

void Marquee(){
  EVERY_N_MILLISECONDS(20){ DrawMarquee(); };
};

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

void nothingElseMatters(){
  h_LEDs[0] = CRGB::Red;     // light LED 0
  h_LEDs[1] = CRGB::Red;     // light LED 1
  h_LEDs[2] = CRGB::Yellow;  // light LED 2
  h_LEDs[3] = CRGB::Yellow;  // light LED 3
  h_LEDs[4] = CRGB::Green;   // light LED 4
  h_LEDs[5] = CRGB::Green;   // light LED 5
  delay(2000);
  FastLED.clear();
};

void PurpleR(){
    FastLED.clear();
    rain.DrawPurpleRain();
    FastLED.show(h_Brightness);
};
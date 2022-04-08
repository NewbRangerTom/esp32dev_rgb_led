//+--------------------------------------------------------------------------
//
// File:         RGB_LED_esp32dev/static.h
//
// Description:
//    Addon to:  NightDriver - (c) 2020 Dave Plummer.  All Rights Reserved.
//
// History:      Feb-10-2022     TW - NewbRanger      Created
//
//--------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

// basic lighting of full strip
void lightFullStrip(){

  for (int i = 0; i < NUM_LEDS; i++)
    h_LEDs[i] = CRGB::Red;

};

// Ukrainian flag colors half blue - half yellow
void UkrainFlag(){

  FastLED.clear();
  for (int i = 0; i < UF_LEDS; i++){
    h_LEDs[i] = CRGB::Yellow;
  }
  for (int j = UF_LEDS; j < NUM_LEDS; j++){
    h_LEDs[j] = CRGB::Blue;
  }
  FastLED.show(h_Brightness);

};
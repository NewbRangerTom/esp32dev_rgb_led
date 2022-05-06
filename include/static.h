//+--------------------------------------------------------------------------
//
// File:         RGB_LED_esp32dev/static.h
//
// Description:
//    Static patterns
//
// History:      Feb-10-2022     TW - NewbRangerTom      Created
//               Apr-8-2022      TW - NewbRangerTom      nothingElseMatters() for init confirmation
//
//--------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

void clearLEDs(){
  FastLED.clear();
};

void firstLED(){
  h_LEDs[0] = CRGB::Red;   // light LED 0
};

// basic lighting of full strip
void lightFullStrip(){

  for (int i = 0; i < NUM_LEDS; i++)
    h_LEDs[i] = CRGB::Red;

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

void Plaid(){
  fill_solid(h_LEDs, NUM_LEDS, CRGB::Plaid);
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
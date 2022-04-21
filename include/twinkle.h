//+--------------------------------------------------------------------------
//
// NightDriver - (c) 2020 Dave Plummer.  All Rights Reserved.
//
// File:          RGB_LED_esp32dev/twinkle.h
//
// Description:
//
//   
//
// History:     Sep-15-2020     davepl      Created
//
//---------------------------------------------------------------------------

#include <Arduino.h>
#define FASTLED_INTERNAL
#include <FastLED.h>

#define TWINKLE_SPEED   50      //  value in milliseconds, best results under 100
#define P_TWINKLE_SPEED 60      //  value in milliseconds, best results under 100
#define NUM_COLORS      5       //  size of the TwinkleColors array

static const CRGB TwinkleColors [NUM_COLORS] = 
{
    CRGB::Red,
    CRGB::Blue,
    CRGB::Purple,
    CRGB::Green,
    CRGB::Yellow
};

static const CRGB PurpleColors [NUM_COLORS] =
{
    CRGB::DarkBlue,
    CRGB::Purple,
    CRGB::BlueViolet,
    CRGB::Violet,
    CRGB::DarkViolet
};

void DrawTwinkle(){

    static int passCount = 0;
    passCount++;

    //  Every time passCount hits a quarter of the LED total, we reset the strip
    if (passCount == NUM_LEDS){

        passCount = 0;
        FastLED.clear(false);                                        //  Clear the strip, but don't push the bits out yet
    }

    h_LEDs[random(NUM_LEDS)] = TwinkleColors[random(NUM_COLORS)];
    delay(TWINKLE_SPEED);
}

void DrawPurpleTwinkle(){

    static int passCount = 0;
    passCount++;

    //  Every time passCount hits a quarter of the LED total, we reset the strip
    if (passCount == NUM_LEDS / 3){

        passCount = 0;
        FastLED.clear(false);                                        //  Clear the strip, but don't push the bits out yet
    }

    h_LEDs[random(NUM_LEDS)] = PurpleColors[random(NUM_COLORS)];
    delay(TWINKLE_SPEED);
}

void DrawTwinkleOg()
{
    FastLED.clear(false);                                           //  Clear the strip, but don't push out the bits yet

    for (int i = 0; i < NUM_LEDS / 4; i++){
        h_LEDs[random(NUM_LEDS)] = TwinkleColors[random(NUM_COLORS)];
        FastLED.show(h_Brightness);
        delay(200);
    }
}

void DrawTwinkleOgTwo(){

    static int passCount = 0;
    passCount++;

    //  Every time passCount hits a quarter of the LED total, we reset the strip
    if (passCount == NUM_LEDS){

        passCount = 0;
        FastLED.clear(false);                                        //  Clear the strip, but don't push out the bits yet
    }

    h_LEDs[random(NUM_LEDS)] = TwinkleColors[random(NUM_COLORS)];
    // delay(200);
}
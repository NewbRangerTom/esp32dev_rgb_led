RGB LED project based on:
-    Dave Plummer's Garage LED Series:
     -   Github repo:       https://github.com/davepl/DavesGarageLEDSeries
     -   YoutTube playlist: https://www.youtube.com/playlist?list=PLF2KJ6Gy3cZ7ynsp8s4tnqEFmY15CKhmH

Draw a pattern or effect using addressable LEDs (WS2812B) using an ESP32 microcontroller.
Select a pattern or effect from a list using Bluetooth connected app.

Added patterns or effects:
-    Ukrain Flag static effect. Half strip yellow, half strip blue.
-    Two variations of the FireEffect: IceFireEffect in a blue palette, Purple Rain in a purple palette
     -   be sure to add the code from the included color_palette.txt to the appropriate FastLED/colorutils files.
-    Bluetooth connectivity with BluetoothSerial.h
     -   Allows for connectivity to android device to switch patterns/effects
    
Control app created using MIT App Inventor
-    http://appinventor.mit.edu/
-    I am not an app developer so this was an easy way to build something fast.
     -   appinventor files included in repo.

MIT App Inventor .aia for importing to App Inventor.

MIT App Inventor .apk file for installing to android device for testing.

Updated 4-25-22

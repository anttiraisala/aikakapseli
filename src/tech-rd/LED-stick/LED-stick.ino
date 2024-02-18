// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include "Adafruit_NeoPixel.h"
#ifdef __AVR__
    #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            4

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      10

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels0 = Adafruit_NeoPixel(10, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(10, 3, NEO_GRB + NEO_KHZ800);

int delayval = 300; // delay for half a second

void setup() {
  randomSeed(analogRead(0));

    // End of trinket special code
    pixels0.setBrightness(255);
    pixels0.begin(); // This initializes the NeoPixel library.
    pixels1.setBrightness(255);
    pixels1.begin(); // This initializes the NeoPixel library.
}

void loop() {

    // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

    for (int i = 0; i < NUMPIXELS; i++) {
       for (int j = 0; j < NUMPIXELS; j++) {
pixels0.setPixelColor(j, pixels0.Color(0, 0, 0));
pixels1.setPixelColor(j, pixels1.Color(0, 0, 0));
       }

        // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
        pixels0.setPixelColor(0, pixels0.Color(random(256), random(256), random(256))); // Moderately bright green color.
        pixels1.setPixelColor(0, pixels1.Color(random(256), random(256), random(256))); // Moderately bright green color.

        pixels0.setPixelColor(i, pixels0.Color(random(256), random(256), random(256))); // Moderately bright green color.
        pixels1.setPixelColor(i, pixels1.Color(random(256), random(256), random(256))); // Moderately bright green color.

        pixels0.show(); // This sends the updated pixel color to the hardware.
        pixels0.setBrightness(random(256));
        pixels1.show(); // This sends the updated pixel color to the hardware.
        pixels1.setBrightness(random(256));

        delay(delayval); // Delay for a period of time (in milliseconds).

    }
}
/*#include "neopixel.h"
#include "math.h"*/

#define tiltPin D7
int tiltState=0;
int tiltStateNew = 0;
float tiltStateBelief = 0;

/*
// set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D1
#define PIXEL_COUNT 8
#define PIXEL_TYPE WS2812B


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);*/

void setup() {
  pinMode(tiltPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  tiltStateNew = digitalRead(tiltPin);
  delay(20);
  if(tiltStateNew == digitalRead(tiltPin)){
    tiltStateBelief = ((tiltStateBelief*9) + tiltStateNew)/10;
    if (tiltStateBelief > 0.9) {
      if (tiltState == 0) {
        Particle.publish("water","on",60,PRIVATE);
        tiltState=tiltStateNew;
        Serial.println("water on");
        // do the light animation going up
        delay(2000);
      }
    }
    else {
      if (tiltState == 1) {
        Particle.publish("water","off",60,PRIVATE);
        tiltState = 0;
        Serial.println("water off");
        // do the light animation going down
        delay(2000);
      }
    }
  }
}


/*void loop() {
  tiltStateNew = digitalRead(tiltPin);
  delay(50);
  if(tiltStateNew == digitalRead(tiltPin)){
    if (tiltStateNew == 1) {
      if (tiltState == 0) {
        Particle.publish("water","on",60,PRIVATE);
        tiltState=tiltStateNew;
        Serial.println("water on");
        // do the light animation going up
        delay(2000);
      }
    }
    else {
      if (tiltState == 1) {
        Particle.publish("water","off",60,PRIVATE);
        tiltState = 0;
        Serial.println("water off");
        // do the light animation going down
        delay(2000);
      }
    }
  }
}
*/

/*// Set all pixels in the strip to a solid color, then wait (ms)
void colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}*/

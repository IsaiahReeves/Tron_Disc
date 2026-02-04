#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUM_LEDS 120
#define BRIGHTNESS 15

// Pulse yellow
#define PULSE_R 255
#define PULSE_G 150
#define PULSE_B 0

// Base purple
/*
#define BASE_R 77
#define BASE_G 0
#define BASE_B 240
*/
#define BASE_R 255
#define BASE_G 51
#define BASE_B 0

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 100;
int pulsePos = 0;

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Reset LEDs to base color
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, BASE_R, BASE_G, BASE_B);
    }

    // Pulse with fading edges
    int pulseWidth = 12;
    for (int i = -pulseWidth / 2; i <= pulseWidth / 2; i++) {
      int index = pulsePos + i;
      if (index < 0) index += NUM_LEDS;
      if (index >= NUM_LEDS) index -= NUM_LEDS;

      float distance = abs(i);
      float fade = 1.0 - (distance / (pulseWidth / 2.0));
      if (fade < 0) fade = 0;

      // Blend channels manually
      uint8_t r = BASE_R + (PULSE_R - BASE_R) * fade;
      uint8_t g = BASE_G + (PULSE_G - BASE_G) * fade;
      uint8_t b = BASE_B + (PULSE_B - BASE_B) * fade;

      strip.setPixelColor(index, r, g, b);  // <-- Pass separate r,g,b
    }

    strip.show();

    // Advance pulse
    pulsePos++;
    if (pulsePos >= NUM_LEDS) pulsePos = 0;
  }
}

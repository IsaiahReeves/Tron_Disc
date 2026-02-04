#include <Adafruit_NeoPixel.h>

#define PIN1 6
#define PIN2 9
#define STRIP_1_NUM_LEDS 27
#define STRIP_2_NUM_LEDS 39
#define BRIGHTNESS 200

// Pulse pink
#define PULSE_R 255
#define PULSE_G 16
#define PULSE_B 52

// Base purple
#define BASE_R 217
#define BASE_G 0
#define BASE_B 162


Adafruit_NeoPixel strip1(STRIP_1_NUM_LEDS, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(STRIP_2_NUM_LEDS, PIN2, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 200;
int pulsePos = 0;

void setup() {
  strip1.begin();
  strip1.setBrightness(BRIGHTNESS);
  strip1.fill(strip1.Color(BASE_R, BASE_G, BASE_B), 0, 0);
  strip1.show();
  strip2.begin();
  strip2.setBrightness(BRIGHTNESS);
  for (int i = 0; i < 19; i++) {
    if (i < 2) {
      strip2.setPixelColor(i + 37, strip2.Color(BASE_R, BASE_G, BASE_B));
      strip2.setPixelColor(36 - i, strip2.Color(BASE_R, BASE_G, BASE_B));
    }
    else {
      strip2.setPixelColor(i - 2, strip2.Color(BASE_R, BASE_G, BASE_B));
      strip2.setPixelColor(36 - i, strip2.Color(BASE_R, BASE_G, BASE_B));
    }
    strip2.show();
    delay(50);
  }
  strip2.setPixelColor(17, strip2.Color(BASE_R, BASE_G, BASE_B));
  strip2.show();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Reset LEDs to base color
    for (int i = 0; i < STRIP_1_NUM_LEDS; i++) {
      strip1.setPixelColor(i, BASE_R, BASE_G, BASE_B);
    }

    // Pulse with fading edges
    int pulseWidth = 12;
    for (int i = -pulseWidth / 2; i <= pulseWidth / 2; i++) {
      int index = pulsePos + i;
      if (index < 0) index += STRIP_1_NUM_LEDS;
      if (index >= STRIP_1_NUM_LEDS) index -= STRIP_1_NUM_LEDS;

      float distance = abs(i);
      float fade = 1.0 - (distance / (pulseWidth / 2.0));
      if (fade < 0) fade = 0;

      // Blend channels manually
      uint8_t r = BASE_R + (PULSE_R - BASE_R) * fade;
      uint8_t g = BASE_G + (PULSE_G - BASE_G) * fade;
      uint8_t b = BASE_B + (PULSE_B - BASE_B) * fade;

      strip1.setPixelColor(index, r, g, b);  // <-- Pass separate r,g,b
    }

    strip1.show();

    // Advance pulse
    pulsePos++;
    if (pulsePos >= STRIP_1_NUM_LEDS) pulsePos = 0;
  }
  
  //strip2.setPixelColor(37, strip2.Color(BASE_R, BASE_G, BASE_B));
  //strip2.setPixelColor(0, strip2.Color(BASE_R, BASE_G, BASE_B));
  /*
  strip2.clear();
  for (int i = 0; i < strip2.numPixels(); i++) {
    strip2.setPixelColor(i, strip2.Color(BASE_R, BASE_G, BASE_B));
    strip2.show();
    delay(50);
  }*/
}

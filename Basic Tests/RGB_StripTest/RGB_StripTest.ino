#include <Adafruit_NeoPixel.h>

#define LED_PIN    6      // Pin connected to the LED strip
#define LED_COUNT  80     // Number of LEDs

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

// Helper: smoothly fade from one color to another
void fadeColor(uint8_t r1, uint8_t g1, uint8_t b1,
               uint8_t r2, uint8_t g2, uint8_t b2,
               int steps, int delayTime) {
  for (int s = 0; s <= steps; s++) {
    uint8_t r = r1 + (r2 - r1) * s / steps;
    uint8_t g = g1 + (g2 - g1) * s / steps;
    uint8_t b = b1 + (b2 - b1) * s / steps;
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
    delay(delayTime);
  }
}

void loop() {
  // Smoothly fade through rainbow colors
  fadeColor(255,   0,   0, 255, 127,   0, 100, 10); // Red → Orange
  fadeColor(255, 127,   0, 255, 255,   0, 100, 10); // Orange → Yellow
  fadeColor(255, 255,   0,   0, 255,   0, 100, 10); // Yellow → Green
  fadeColor(  0, 255,   0,   0, 255, 255, 100, 10); // Green → Cyan
  fadeColor(  0, 255, 255,   0,   0, 255, 100, 10); // Cyan → Blue
  fadeColor(  0,   0, 255, 128,   0, 255, 100, 10); // Blue → Violet
  fadeColor(128,   0, 255, 255,   0,   0, 100, 10); // Violet → Red
}

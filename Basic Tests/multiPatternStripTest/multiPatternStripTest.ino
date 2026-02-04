#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT  120

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// --- Animation settings ---
int waveOffset = 0;
int pulsePhase = 0;

void setup() {
  strip.begin();
  strip.show();
}

// Helper: rainbow color generator
uint32_t wheel(byte pos) {
  if (pos < 85) {
    return strip.Color(pos * 3, 255 - pos * 3, 0);
  } else if (pos < 170) {
    pos -= 85;
    return strip.Color(255 - pos * 3, 0, pos * 3);
  } else {
    pos -= 170;
    return strip.Color(0, pos * 3, 255 - pos * 3);
  }
}

void loop() {
  strip.clear();

  // --- Section 1: Rainbow wave (LEDs 0–39) ---
  for (int i = 0; i < 40; i++) {
    int colorIndex = (i * 256 / 40 + waveOffset) & 255;
    strip.setPixelColor(i, wheel(colorIndex));
  }
  waveOffset++; // Move the rainbow over time

  // --- Section 2: Solid color (LEDs 40–79) ---
  uint32_t solidColor = strip.Color(255, 255, 255); // blue
  for (int i = 40; i < 80; i++) {
    strip.setPixelColor(i, solidColor);
  }

  // --- Section 3: Pulsing color (LEDs 80–119) ---
  int brightness = (sin(pulsePhase * 3.14159 / 180.0) + 1) * 127; // 0–255 sinusoid
  uint32_t pulseColor = strip.Color(brightness, 0, brightness / 4);
  for (int i = 80; i < 120; i++) {
    strip.setPixelColor(i, pulseColor);
  }
  pulsePhase = (pulsePhase + 5) % 360;

  strip.show();
  delay(30);
}

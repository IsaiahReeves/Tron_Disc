#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT  120

int red;
int green;
int blue;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(analogRead(A1));
}

void loop() {
  // Light up each LED individually with different colors
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.clear(); // Turn off all LEDs first

    red = random(0, 255);
    green = random(0, 255);
    blue = random(0, 255);

    Serial.print("Color = ");
    Serial.print(", ");
    Serial.print(red);
    Serial.print(", ");
    Serial.print(green);
    Serial.print(", ");
    Serial.println(blue);

    // Pick a color based on the index
    if (i % 3 == 0)
      strip.setPixelColor(i, strip.Color(red, green, blue));  // Red
    else if (i % 3 == 1)
      strip.setPixelColor(i, strip.Color(red, green, blue));  // Green
    else
      strip.setPixelColor(i, strip.Color(red, green, blue));  // Blue

    strip.show();
    delay(100);
  }
}

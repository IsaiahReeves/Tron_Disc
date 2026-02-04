//Test program for the RGB abilites of the LED strip
#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT  120

int red;
int green;
int blue;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //Optional Serial initialization for debugging
  //Serial.begin(115200);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  randomSeed(analogRead(A1));
}

void loop() {
  // Light up each LED individually with different colors
  strip.clear();
  for (int i = 0; i < strip.numPixels(); i++) {
    //strip.clear(); Turn off all LEDs first
    //Randomize the Color for each LED on the strip
    red = random(0, 255);
    green = random(0, 255);
    blue = random(0, 255);
    
    strip.setPixelColor(i, strip.Color(100, 150, 200));
    strip.show();
    //Timing of the LED strip in ms
    delay(50);

    
    /* Printing the Color of the LEDs for debugging 
    Serial.print("Color = ");
    Serial.print(", ");
    Serial.print(red);
    Serial.print(", ");
    Serial.print(green);
    Serial.print(", ");
    Serial.println(blue);
    */
  }
}

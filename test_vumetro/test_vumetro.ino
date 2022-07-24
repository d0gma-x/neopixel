#include <Adafruit_NeoPixel.h>
#define PIXEL_PIN 6
#define PIXEL_COUNT 12
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

const int sampleWindow = 10; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
int mode = 0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.setBrightness(10); //0 - 255
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(0);
    if (sample < 1024) {
      if (sample > signalMax) {
        signalMax = sample;  // save just the max levels
      }
      else if (sample < signalMin)
      {
        signalMin = sample;  // save just the min levels
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
  double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  //  mode = map(volts, 0, 3.3, 0, 6);
  //  Serial.println(volts);
  mode = map(peakToPeak, 0, 750, 0, 7);
  Serial.println(peakToPeak);
  if (++mode > 7) mode = 0; // Advance to next mode, wrap around after #8
  switch (mode) {          // Start the new animation...
    case 0:
      colorWipe(strip.Color(0, 0, 0), 0); //off
      break;
    case 1:
      colorWipe(strip.Color(0, 255, 255), 0); //cyan
      break;
    case 2:
      colorWipe(strip.Color(0, 255, 0), 0); //green
      break;
    case 3:
      colorWipe(strip.Color(255, 255, 0), 0); //yellow
      break;
    case 4:
      colorWipe(strip.Color(255, 127, 0), 0); //orange
      break;
    case 5:
      colorWipe(strip.Color(255, 0, 0), 0); //red
      break;
    case 6:
      colorWipe(strip.Color(255, 0, 255), 0); //magenta
      break;
    case 7:
      colorWipe(strip.Color(0, 0, 255), 0); //blue
      break;
  }
}
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    //delay(wait);                           //  Pause for a moment
  }
}

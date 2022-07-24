#include <Adafruit_NeoPixel.h>
#include "U8glib.h"

#define PIXEL_PIN 6
#define PIXEL_COUNT 12
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

const int sampleWindow = 15; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
int mode = 0;
float db;

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(250); //0 - 255
  strip.show(); // Initialize all pixels to 'off'
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
  }
}

void draw(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.setPrintPos(0, 10);
  u8g.print(db);
  u8g.setPrintPos(35, 10);
  u8g.print(" dB");
}

void loop(void) {
  unsigned long startMillis = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level
  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;

  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(0);
    if (sample < 1024) {
      if (sample > signalMax) {
        signalMax = sample;
      }
      else if (sample < signalMin)
      {
        signalMin = sample;
      }
    }
  }
  peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude

  //  double volts = (peakToPeak * 5.0) / 1024;  // convert to volts
  //  mode = map(volts, 0, 3.3, 0, 9);
  //  Serial.println(volts);

  db = map(peakToPeak, 20, 900, 49.5, 90);
  mode = map(db, 49.5, 90, 0, 9);
  Serial.println(db);

  u8g.firstPage();
  do {
    draw();
  } while (u8g.nextPage() );

  //  mode = map(peakToPeak, 0, 650, 0, 9);
  //  Serial.println(peakToPeak);
  //    Serial.println(sample);

  if (++mode > 9) mode = 0;
  switch (mode) {
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
    case 8:
      colorWipe(strip.Color(255, 0, 127), 0); //red + magenta
      break;
    case 9:
      colorWipe(strip.Color(127, 0, 255), 0); //blue + magenta
      break;

      //      colorWipe(strip.Color(0, 255, 167), 0); //green + cyan
      //      colorWipe(strip.Color(127, 255, 0), 0); //green + yellow
      //      colorWipe(strip.Color(255, 0, 127), 0); //red + magenta
      //      colorWipe(strip.Color(0, 127, 255), 0); //blue + cyan
  }
}

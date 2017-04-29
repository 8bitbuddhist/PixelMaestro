#include <Arduino.h>
#include "../include/Colors.h"
#include "../include/Maestro.h"
#include "../include/Pixel.h"
#include "../include/Section.h"

#include <WS2812.h>

using namespace PixelMaestro;

const unsigned char rows = 1;
const unsigned char columns = 8;
const unsigned char numPixels = rows * columns;

Maestro maestro;
Section sections[1];
Pixel pixels[numPixels];

// WS1812 stuff
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(numPixels);

const float MAX_BRIGHTNESS = 0.1;

cRGB RGBtoCRGB(Colors::RGB rgbColor);

cRGB RGBtoCRGB(Colors::RGB rgbColor) {
  cRGB cRGBColor;
  cRGBColor.r = rgbColor.r * MAX_BRIGHTNESS;
  cRGBColor.g = rgbColor.g * MAX_BRIGHTNESS;
  cRGBColor.b = rgbColor.b * MAX_BRIGHTNESS;
  return cRGBColor;
}

void setup() {
    ws.setOutput(LED_PIN);
    ws.setColorOrderGRB();

    sections[0].setColors(Colors::COLORWHEEL, 12);
    sections[0].setPixels(pixels, rows, columns);
    sections[0].setColorAnimation(Section::ColorAnimations::MERGE, true);
    maestro.setSections(sections, 1);
}

void loop() {
    maestro.update(millis());

    for (unsigned char pixel = 0; pixel < numPixels; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(maestro.getSection(0)->getPixelColor(pixel)));
    }

    ws.sync();
}

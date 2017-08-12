#include "../../src/Colors.h"
#include "../../src/Maestro.h"
#include "../../src/Pixel.h"
#include "../../src/Section.h"

#include "../.piolibdeps/LightWS2812_ID159/WS2812.h"

using namespace PixelMaestro;

const unsigned char rows = 1;
const unsigned char columns = 8;
const unsigned char numPixels = rows * columns;
const float MAX_BRIGHTNESS = 0.10;

Maestro maestro;
Pixel pixels[numPixels];
Section sections[] = {
  Section(pixels, rows, columns)
};

// WS1812 stuff
const unsigned char LED_PIN = 5;
WS2812 ws = WS2812(numPixels);

cRGB RGBtoCRGB(Colors::RGB rgbColor);

void setup () {
    sections[0].setColors(Colors::COLORWHEEL, 12);
    sections[0].setColorAnimation(Section::ColorAnimations::MERGE, false);
    maestro.setSections(sections, 1);
}

void loop() {
    maestro.update(millis());

    for (unsigned char pixel = 0; pixel < numPixels; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(maestro.getSection(0)->getPixelColor(pixel)));
    }

    ws.sync();
}

cRGB RGBtoCRGB(Colors::RGB rgbColor) {
  cRGB cRGBColor;
  cRGBColor.r = rgbColor.r * MAX_BRIGHTNESS;
  cRGBColor.g = rgbColor.g * MAX_BRIGHTNESS;
  cRGBColor.b = rgbColor.b * MAX_BRIGHTNESS;
  return cRGBColor;
}

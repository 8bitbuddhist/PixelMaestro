#include <Arduino.h>

#include <PixelMaestro/animation/solidanimation.h>
#include <PixelMaestro/core/maestro.h>

#include <WS2812.h>

using namespace PixelMaestro;

const unsigned char ROWS = 1;
const unsigned char COLUMNS = 8;
const unsigned char NUM_PIXELS = ROWS * COLUMNS;
const float MAX_BRIGHTNESS = 0.05;

Maestro maestro;
Pixel pixels[NUM_PIXELS];
Section sections[] = {
  Section(pixels, new Point(ROWS, COLUMNS))
};

// WS1812 stuff
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(NUM_PIXELS);
cRGB RGBtoCRGB(Colors::RGB rgbColor) {
  cRGB cRGBColor;
  cRGBColor.r = rgbColor.r * MAX_BRIGHTNESS;
  cRGBColor.g = rgbColor.g * MAX_BRIGHTNESS;
  cRGBColor.b = rgbColor.b * MAX_BRIGHTNESS;
  return cRGBColor;
}

void setup () {
    ws.setOutput(LED_PIN);
    ws.setColorOrderGRB();

    sections[0].set_animation(new SolidAnimation(&sections[0], Colors::COLORWHEEL, 12));

    maestro.set_sections(sections, 1);
}

void loop() {
    maestro.update(millis());

    for (unsigned char pixel = 0; pixel < NUM_PIXELS; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(sections[0].get_pixel_color(pixel)));
    }

    ws.sync();
}

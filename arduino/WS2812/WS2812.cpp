#include <Arduino.h>

#include <PixelMaestro/animation/solidanimation.h>
#include <PixelMaestro/core/maestro.h>

#include <WS2812.h>

using namespace PixelMaestro;

const unsigned char ROWS = 1;
const unsigned char COLUMNS = 8;

Section sections[] = {
  Section(ROWS, COLUMNS)
};
Maestro maestro(sections, 1);

// WS1812 stuff
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(ROWS * COLUMNS);
cRGB RGBtoCRGB(Colors::RGB rgbColor) {
  cRGB cRGBColor;
  cRGBColor.r = rgbColor.r;
  cRGBColor.g = rgbColor.g;
  cRGBColor.b = rgbColor.b;
  return cRGBColor;
}

void setup () {
    ws.setOutput(LED_PIN);
    ws.setColorOrderGRB();

		maestro.set_brightness(0.1);
    maestro.get_section(0)->set_animation(new SolidAnimation(Colors::COLORWHEEL, 12));
}

void loop() {
    maestro.update(millis());

    for (unsigned char pixel = 0; pixel < ROWS * COLUMNS; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(maestro.get_pixel_color(0, pixel)));
    }

    ws.sync();
}

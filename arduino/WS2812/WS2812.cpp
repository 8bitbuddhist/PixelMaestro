#include <Arduino.h>

#include <PixelMaestro/animation/solidanimation.h>
#include <PixelMaestro/core/maestro.h>

#include <WS2812.h>

using namespace PixelMaestro;

const unsigned char ROWS = 1;
const unsigned char COLUMNS = 8;
const float MAX_BRIGHTNESS = 0.05;

Section sections[] = {
  Section(new Point(ROWS, COLUMNS))
};
Maestro maestro(sections, 1);

// WS1812 stuff
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(ROWS * COLUMNS);
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

    maestro.get_section(0)->set_animation(new SolidAnimation(&sections[0], Colors::COLORWHEEL, 12));
}

void loop() {
    maestro.update(millis());

    for (unsigned char pixel = 0; pixel < ROWS * COLUMNS; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(maestro.get_section(0)->get_pixel_color(pixel)));
    }

    ws.sync();
}

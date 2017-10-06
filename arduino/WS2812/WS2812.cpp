#include <Arduino.h>

#include <PixelMaestro/core/maestro.h>

#include <WS2812.h>

using namespace PixelMaestro;

const unsigned char ROWS = 8;
const unsigned char COLUMNS = 1;

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

		// Set global brightness to 10%
		maestro.set_brightness(25);

		// Create a new blinking animation, set a palette of 12 colors, and set the cycle speed to 500ms
		Animation* animation = sections[0].set_animation(AnimationType::Type::Blink, Colors::COLORWHEEL, 12);
		animation->set_speed(500);
}

void loop() {
    maestro.update(millis());

    for (unsigned char pixel = 0; pixel < ROWS * COLUMNS; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(maestro.get_pixel_color(0, pixel)));
    }

    ws.sync();
}

#include <Arduino.h>

#include <PixelMaestro/core/maestro.h>

#include <WS2812.h>

using namespace PixelMaestro;

// Create a Maestro with a Section 8 pixels wide and 1 pixel high
Maestro maestro(8, 1);

// WS1812 stuff
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(maestro.get_section(0)->get_dimensions()->size());
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

		// Create a new blinking animation, set a new Palette, then set the speed to 500ms.
		Animation* animation = maestro.get_section(0)->set_animation(AnimationType::Type::Blink, Colors::COLORWHEEL, 12);
		animation->set_speed(500);
}

void loop() {
    maestro.update(millis());

    for (unsigned char pixel = 0; pixel < maestro.get_section(0)->get_dimensions()->size(); pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(maestro.get_pixel_color(0, pixel)));
    }

    ws.sync();
}

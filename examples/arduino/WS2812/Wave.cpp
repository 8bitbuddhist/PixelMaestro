/*
 * WS2812.cpp - Creates an 8 LED strip using the Light WS2812 library and displays a Wave animation.
 */

#include <Arduino.h>
#include <PixelMaestro/core/maestro.h>
#include <PixelMaestro/colorpresets.h>
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

		// Create a new wave animation, change the palette to ColorWheel, then set the speed to 500ms.
		Animation* animation = maestro.get_section(0)->set_animation(AnimationType::Type::Wave, ColorPresets::COLORWHEEL, 12);
		animation->set_timing(500);
}

void loop() {
    maestro.update(millis());

		for (unsigned char x = 0; x < maestro.get_section(0)->get_dimensions()->x; x++) {
			ws.set_crgb_at(x, RGBtoCRGB(maestro.get_pixel_color(0, x, 0)));
		}

    ws.sync();
}

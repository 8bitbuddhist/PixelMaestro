/*
 * Blink.cpp - Creates an 8 LED NeoPixel strip running a simple Blink animation.
 * Attach your strip to pin 10 on the Arduino (or change LED_PIN).
 */

#include <Arduino.h>
#include <colorpresets.h>
#include <core/maestro.h>
#include <core/palette.h>
#include <Adafruit_NeoPixel.h>

using namespace PixelMaestro;

// Create a Maestro with a single 8x1 Section
Maestro maestro(8, 1);

// Initialize the NeoPixel strip on pin 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maestro.get_section(0)->get_dimensions()->x, 10, NEO_GRB + NEO_KHZ800);

void setup () {
    strip.begin();

		// Set the global brightness to 10%
		maestro.set_brightness(25);

		// Create a new blinking animation and set the color palette to the ColorWheel preset
		Animation* animation = maestro.get_section(0)->set_animation(AnimationType::Blink, new Palette(ColorPresets::Colorwheel, 12));

		// Set the amount of time between animation cycles to 500ms
		animation->set_timer(500);
}

void loop() {
    if (maestro.update(millis())) {
  		// Copy each Pixel's color to the NeoPixel strip
			for (unsigned char x = 0; x < maestro.get_section(0)->get_dimensions()->x; x++) {
				Colors::RGB color = maestro.get_pixel_color(0, x, 0);
				strip.setPixelColor(x, color.r, color.g, color.b);
			}

  		strip.show();
    }
}

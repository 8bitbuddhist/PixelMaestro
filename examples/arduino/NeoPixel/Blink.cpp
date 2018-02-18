/*
 * Blink.cpp - Creates an 8 LED NeoPixel strip that displays a simple Blink animation.
 */

#include <Arduino.h>
#include <PixelMaestro/core/maestro.h>
#include <PixelMaestro/colorpresets.h>
#include <Adafruit_NeoPixel.h>

using namespace PixelMaestro;

// Creates a Maestro with a single 8x1 Section
Maestro maestro(8, 1);

// Initializes the NeoPixel strip on pin 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maestro.get_section(0)->get_dimensions()->x, 10, NEO_GRB + NEO_KHZ800);

void setup () {
    strip.begin();

		// Sets the global brightness to 10%
		maestro.set_brightness(25);

		// Creates a new blinking animation and sets the color palette to the ColorWheel preset
		Animation* animation = maestro.get_section(0)->set_animation(AnimationType::Blink, ColorPresets::Colorwheel, 12);

		// Sets the amount of time between animation cycles to 500ms
		animation->set_timer(500);
}

void loop() {
    if (maestro.update(millis())) {
  		// Copies each Pixel's color to the NeoPixel strip
  		for (unsigned char y = 0; y < maestro.get_section(0)->get_dimensions()->y; y++) {
  			for (unsigned char x = 0; x < maestro.get_section(0)->get_dimensions()->x; x++) {
  				Colors::RGB color = maestro.get_pixel_color(0, x, y);
  				strip.setPixelColor(x, color.r, color.g, color.b);
  			}
  		}

  		strip.show();
    }
}

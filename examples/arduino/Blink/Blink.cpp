/*
 * Blink.cpp - Creates an 8 LED NeoPixel strip running a simple Blink animation.
 * Attach your strip to pin 10 on the Arduino (or change LED_PIN).
 */

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <colorpresets.h>
#include <core/maestro.h>

using namespace PixelMaestro;

// Create a Maestro with a single 8x1 Section
Maestro maestro(8, 1);
Section* section = maestro.get_section(0);

// Initialize the NeoPixel strip on pin 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maestro.get_section(0)->get_dimensions().x, 10, NEO_GRB + NEO_KHZ800);

// Create a basic palette
Colors::RGB palette_colors[] = {ColorPresets::White};
Palette palette = Palette(palette_colors, 1);

void setup () {
	strip.begin();

	// Set the global brightness to 10%
	maestro.set_brightness(25);

	// Create the animation and set the amount of time between cycles to 1 second
	Animation& animation = maestro.get_section(0)->set_animation(AnimationType::Blink);
	animation.set_palette(palette);
	animation.set_timer(1000);
}

void loop() {
	if (maestro.update(millis())) {
		// Copy each Pixel's color to the NeoPixel strip
		uint8_t led = 0;
		for (uint8_t y = 0; y < section->get_dimensions().y; y++) {
			for (uint8_t x = 0; x < section->get_dimensions().x; x++) {
				Colors::RGB color = maestro.get_pixel_color(0, x, 0);
			strip.setPixelColor(led, color.r, color.g, color.b);
				led++;
			}
		}

		strip.show();
	}
}

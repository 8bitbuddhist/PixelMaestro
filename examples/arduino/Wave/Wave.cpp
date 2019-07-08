/*
 * Wave.cpp - Creates an 8 LED strip and displays a Wave animation.
 * Attach your strip to pin 10, or change LED_PIN to use a different pin.
 */

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <PixelMaestro.h>
#include <core/maestro.h>
#include <colorpresets.h>

using namespace PixelMaestro;

// Create a Maestro with a Section 8 pixels wide and 1 pixel high
Maestro maestro(8, 1);
Section* section = maestro.get_section(0);

// Initialize the NeoPixel strip on pin 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maestro.get_section(0)->get_dimensions().size(), 10, NEO_GRB + NEO_KHZ800);

void setup () {
	strip.begin();

	// Set global brightness to 10%
	maestro.set_brightness(25);

	// Create a new wave animation, change the palette to ColorWheel, then set the speed to 500ms.
	Animation& animation = section->set_animation(AnimationType::Wave);
	animation.set_palette(ColorPresets::Colorwheel_Palette);
	animation.set_timer(500);
}

void loop() {
	if (maestro.update(millis())) {
		uint8_t led = 0;
		for (uint8_t y = 0; y < section->get_dimensions().y; y++) {
			for (uint8_t x = 0; x < section->get_dimensions().x; x++) {
				Colors::RGB color = section->get_pixel_color(x, y);
				strip.setPixelColor(led, color.r, color.g, color.b);
				led++;
			}
		}

		strip.show();
	}
}

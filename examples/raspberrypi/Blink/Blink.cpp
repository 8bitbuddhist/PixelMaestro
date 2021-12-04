/*
 * Blink.cpp - Creates an 8 LED NeoPixel strip running a simple Blink animation.
 * Attach your strip to pin 10 on the Arduino (or change LED_PIN).
 */

#include "ws2812-rpi.h"
#include <PixelMaestro.h>
#include <core/maestro.h>
#include <colorpresets.h>

using namespace PixelMaestro;

int main(int argc, char **argv){
    // Create a Maestro with a single 8x1 Section
    Maestro maestro(8, 1, 1);
    Section* section = maestro.get_section(0);

    // Initialize the NeoPixel strip
    NeoPixel *strip=new NeoPixel(section.get_dimensions());
    strip.begin();

	// Set the global brightness to 10%
	maestro.set_brightness(25);

    // Create a basic palette
    Colors::RGB palette_colors[] = {ColorPresets::White};
    Palette palette = Palette(palette_colors, 1);

	// Create the animation and set the amount of time between cycles to 1 second
	Animation& animation = maestro.get_section(0)->set_animation(AnimationType::Blink);
	animation.set_palette(palette);
	animation.set_timer(1000);

    while(true) {
        if (maestro.update(millis())) {
		// Copy each Pixel's color to the WS2812 strip
		uint32_t led = 0;
		for (uint16_t y = 0; y < section->get_dimensions().y; y++) {
			for (uint16_t x = 0; x < section->get_dimensions().x; x++) {
				Colors::RGB color = section->get_pixel_color(x, y);
			    strip.setPixelColor(led, color.r, color.g, color.b);
				led++;
			}
		}

		strip.show();
    }
    delete strip;

    return 0;
}
/*
 * NeoPixel.cpp - Creates an 8 LED NeoPixel strip that listens for Cues.
 * You can control the strip by connecting the Arduino to PixelMaestro Studio over USB.
 */

#include <Arduino.h>
#include <PixelMaestro/core/maestro.h>
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

		/*
		 * Initializes the Cue Controller and CueHandlers.
		 * To reduce the program size, only enable the CueHandlers you need.
		 */
		CueController* controller = maestro.set_cue_controller();
    controller->enable_animation_cue_handler();
    controller->enable_canvas_cue_handler();
    controller->enable_maestro_cue_handler();
    controller->enable_section_cue_handler();
    controller->enable_show_cue_handler();

		Serial.begin(9600);
}

void loop() {
		// Listens for incoming Cues
		if (Serial.available()) {
			maestro.get_cue_controller()->read(Serial.read());
		}

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

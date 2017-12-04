/*
 * NeoPixel.cpp - Configures an 8 LED NeoPixel strip.
 * You can control the strip by connecting to its controlling Arduino using PixelMaestro Studio.
 */

#include <Arduino.h>
#include <PixelMaestro/core/maestro.h>
#include <Adafruit_NeoPixel.h>

using namespace PixelMaestro;

// Creates a Maestro with a single Section
Maestro maestro(8, 1);

// Initializes the NeoPixel strip on pin 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maestro.get_section(0)->get_dimensions()->x, 10, NEO_GRB + NEO_KHZ800);

void setup () {
    strip.begin();

		maestro.set_brightness(25);
		CueController* controller = maestro.set_cue_controller();
		controller->enable_handler(CueController::Handler::AnimationHandler);
		controller->enable_handler(CueController::Handler::CanvasHandler);
		controller->enable_handler(CueController::Handler::MaestroHandler);
		controller->enable_handler(CueController::Handler::SectionHandler);

		Serial.begin(9600);
}

void loop() {
		if (Serial.available()) {
			maestro.get_cue_controller()->read(Serial.read());
		}

    maestro.update(millis());

		for (unsigned char x = 0; x < maestro.get_section(0)->get_dimensions()->x; x++) {
			Colors::RGB color = maestro.get_pixel_color(0, x, 0);
			strip.setPixelColor(x, color.r, color.g, color.b);
		}

		strip.show();
}

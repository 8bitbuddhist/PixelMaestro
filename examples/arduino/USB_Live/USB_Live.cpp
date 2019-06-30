/*
 * USBLive.cpp - Creates an 8 LED NeoPixel strip for use with PixelMaestro Studio.
 *    1) Attach your strip to pin 10 on the Arduino (or change LED_PIN).
 *    2) Connect your Arduino to your computer via USB.
 *    3) Run PixelMaestro Studio and select the Device tab.
 *    4) Add your device (make sure "Live updates" is checked) and click "Connect".
 *    5) Have fun!
 */

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <PixelMaestro.h>
#include <core/maestro.h>
#include <core/section.h>
#include <cue/maestrocuehandler.h>
#include <cue/sectioncuehandler.h>

using namespace PixelMaestro;

// Create a Maestro with a single 8x1 Section
Maestro maestro(8, 1, 1);
Section* section = maestro.get_section(0);

// Initialize the NeoPixel strip on pin 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maestro.get_section(0)->get_dimensions().x, 10, NEO_GRB + NEO_KHZ800);

void setup () {
	strip.begin();

	// Set the global brightness to 10%
	maestro.set_brightness(25);

	/*
	 * Initialize the CueController and CueHandlers.
	 * To reduce the sketch size, disable any unused CueHandlers.
	 */
	CueController& controller = maestro.set_cue_controller();
	controller.enable_animation_cue_handler();
	controller.enable_maestro_cue_handler();
	controller.enable_section_cue_handler();
	controller.enable_canvas_cue_handler();
	controller.enable_show_cue_handler();

	// Block certain Cues from firing.
	const uint8_t num_blocks = 3;
	CueController::BlockedCue* blocks = new CueController::BlockedCue[num_blocks] {
		CueController::BlockedCue(CueController::Handler::MaestroCueHandler, (uint8_t)MaestroCueHandler::Action::SetShow),
		CueController::BlockedCue(CueController::Handler::SectionCueHandler, (uint8_t)SectionCueHandler::Action::SetDimensions),
		CueController::BlockedCue(CueController::Handler::SectionCueHandler, (uint8_t)SectionCueHandler::Action::SetBrightness)
	};

	controller.set_blocked_cues(blocks, num_blocks);

	Serial.begin(9600);
}

void loop() {
	// Listen for incoming Cues
	if (Serial.available()) {
		// Read in the current byte to the CueController
		maestro.get_cue_controller().read(Serial.read());
	}

	// Update the Maestro
	if (maestro.update(millis())) {
		// Copy each Pixel's color to the WS2812 strip
		uint32_t led = 0;
		for (uint16_t y = 0; y < section->get_dimensions().y; y++) {
			for (uint16_t x = 0; x < section->get_dimensions().x; x++) {
				Colors::RGB color = maestro.get_pixel_color(0, x, 0);
			strip.setPixelColor(led, color.r, color.g, color.b);
				led++;
			}
		}

		strip.show();
	}
}
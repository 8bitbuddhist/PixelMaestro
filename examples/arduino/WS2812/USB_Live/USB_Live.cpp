/*
 * USBLive.cpp - Creates an 8 LED NeoPixel strip for use with PixelMaestro Studio.
 *    1) Attach your strip to pin 10 on the Arduino (or change LED_PIN).
 *    2) Connect your Arduino to your computer via USB.
 *    3) Run PixelMaestro Studio and select the Device tab.
 *    4) Select the port that your Arduino is connected to, click "Connect", then check "Live updates".
 *    5) Have fun!
 */

#include <Arduino.h>
#include <PixelMaestro.h>
#include <core/maestro.h>
#include <core/section.h>
#include <colorpresets.h>
#include <animation/waveanimation.h>
#include <WS2812.h>
#include <cRGB.h>

using namespace PixelMaestro;

// Create a Maestro with a single 8x1 Section
Maestro maestro(8, 1, 1);
Section& section = maestro.get_section(0);

// Initialize WS2812 components
const uint8_t LED_PIN = 10;
WS2812 ws = WS2812(section.get_dimensions().size());

// Translate PixelMaestro RGB to LightWS2812 cRGB
cRGB RGBtoCRGB(Colors::RGB rgb) {
	return cRGB {
		rgb.r,
		rgb.g,
		rgb.b
	};
}

void setup () {
	ws.setOutput(LED_PIN);

	// Set the global brightness to 10%
	maestro.set_brightness(15);

	/*
	 * Initialize the CueController and CueHandlers.
	 * To reduce the sketch size, disable any unused CueHandlers.
	 */
	CueController& controller = maestro.set_cue_controller();
	controller.enable_animation_cue_handler();
	controller.enable_canvas_cue_handler();
	controller.enable_maestro_cue_handler();
	controller.enable_section_cue_handler();
	controller.enable_show_cue_handler();

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
		for (uint16_t y = 0; y < section.get_dimensions().y; y++) {
			for (uint16_t x = 0; x < section.get_dimensions().x; x++) {
				ws.set_crgb_at(led, RGBtoCRGB(section.get_pixel_color(x, y)));
				led++;
			}
		}

		ws.sync();
	}
}
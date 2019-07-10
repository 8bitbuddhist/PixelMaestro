/*
 * USB_EEPROM.cpp - Sample sketch for storing a Maestro configuration in EEPROM.
 * 
 *    1) Attach your strip to pin 10 on the Arduino (or change LED_PIN).
 *    2) Connect your Arduino to your computer via USB.
 *    3) Run PixelMaestro Studio and select the Device tab.
 * 	  4) Add your device and click "Connect" (make sure "Live updates" is unchecked).
 *    5) Customize your Maestro and click "Upload".
 *    ^) Have fun!
 */

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <PixelMaestro.h>
#include <core/maestro.h>
#include <core/section.h>
#include <cue/maestrocuehandler.h>
#include <cue/sectioncuehandler.h>
#include <EEPROM.h>

using namespace PixelMaestro;

// Create a Maestro with a single 8x1 Section
Maestro maestro(8, 1);
Section* section = maestro.get_section(0);

// Initialize the NeoPixel strip on pin 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maestro.get_section(0)->get_dimensions().size(), 10, NEO_GRB + NEO_KHZ800);

// Variables to track current position in EEPROM
const uint8_t EEPROM_START = 4;
uint16_t eeprom_index = 0;

void run_eeprom() {
	// Check to see if there's a Cuefile stored in EEPROM. Otherwise, exit.
	if (EEPROM.read(EEPROM_START) != 'P' ||
		EEPROM.read(EEPROM_START + 1) != 'M' ||
		EEPROM.read(EEPROM_START + 2) != 'C') return;

	// Get the size of the Cuefile, then read it into the Maestro.
	uint8_t size_arr[4];
	EEPROM.get(0, size_arr);
	uint32_t size = IntByteConvert::byte_to_uint32(size_arr);
	for (uint16_t i = 0; i < size; i++) {
		maestro.get_cue_controller().read(EEPROM.read(EEPROM_START + i));
	}
}

void setup () {
	strip.begin();

	// Set the global brightness to 10%
	maestro.set_brightness(25);

	/*
	 * Initialize the CueController and CueHandlers.
	 * To reduce the sketch size, comment out any unused CueHandlers.
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

	run_eeprom();
	Serial.begin(9600);
}

void loop() {
	// Listen for incoming Cues
	if (Serial.available()) {
		uint8_t in = Serial.read();

		// Read in the current byte to the CueController
		maestro.get_cue_controller().read(in);

		// Write the byte to EEPROM
		EEPROM.update(EEPROM_START + eeprom_index, in);

		// Check for the "ROMEND" flag. If it's detected, write the size of the Cuefile to EEPROM.
		if (in == 'D' && eeprom_index >= 5) {
			char flag[6];
			EEPROM.get(eeprom_index - 5, flag);
			if (strcmp(flag, "ROMEND") == 0) {
				IntByteConvert size = IntByteConvert(eeprom_index);
				EEPROM.update(0, size.converted_0);
				EEPROM.update(1, size.converted_1);
				EEPROM.update(2, size.converted_2);
				EEPROM.update(3, size.converted_3);
			}
		}

		eeprom_index++;
		if (EEPROM_START + eeprom_index >= EEPROM.length()) eeprom_index = 0;
	}

	// Update the Maestro
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
}
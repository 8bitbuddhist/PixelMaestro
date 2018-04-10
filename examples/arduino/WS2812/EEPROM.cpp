/*
 * NeoPixel.cpp - Creates an 8 LED NeoPixel strip that listens for Cues.
 * You can control the strip by connecting the Arduino to PixelMaestro Studio over USB.
 */

#include <Arduino.h>
#include <EEPROM.h>
#include <PixelMaestro/core/maestro.h>
#include <WS2812.h>

using namespace PixelMaestro;

uint8_t header[6];
uint8_t header_index = 0;
uint16_t eeprom_index = 0;
bool eeprom_read = false;

// Creates a Maestro with a single 8x1 Section
Maestro maestro(8, 1);

// Initialize WS2812 components
const uint8_t LED_PIN = 10;
WS2812 ws = WS2812(maestro.get_section(0)->get_dimensions()->x);

// Runs Cues stored in EEPROM
void run_eeprom_cue() {
  for (uint16_t index = 0; index < EEPROM.length(); index++) {
    maestro.get_cue_controller()->read(EEPROM[index]);
  }
}

void setup () {
    ws.setOutput(LED_PIN);

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

    // If we have Cue data stored in EEPROM, read it in.
    if (EEPROM.read(0) == 'P' && EEPROM.read(1) == 'M' && EEPROM.read(2) == 'C') {
      run_eeprom_cue();
    }

		Serial.begin(9600);
}

void loop() {
		// Listens for incoming Cues
		if (Serial.available()) {
      uint8_t in = Serial.read();

      // Reset the header read index on detecting an EEPROM start/stop command.
      if (in == 'R') {
        header_index = 0;
      }
      header[header_index] = in;
      header_index++;

      // If we're in EEPROM read mode, write the current byte to EEPROM.
      if (eeprom_read) {
        EEPROM.write(eeprom_index, in);
        eeprom_index++;
      }

      // If we read in the EEPROM start header, write the following serial data to EEPROM.
      if (header[0] == 'R' && header[1] == 'O' && header[2] == 'M' && header[3] == 'B' && header[4] == 'E' && header[5] == 'G') {
        eeprom_read = true;
      }
      // If we read in the EEPROM end header, stop writing to EEPROM and reset the eeprom read index.
      else if (header[0] == 'R' && header[1] == 'O' && header[2] == 'M' && header[3] == 'E' && header[4] == 'N' && header[5] == 'D') {
        eeprom_read = false;
        eeprom_index = 0;
        run_eeprom_cue();
      }

      // Reset the EEPROM counter.
      if (eeprom_index >= EEPROM.length()) {
        eeprom_index = 0;
        eeprom_read = false;
      }
      // Reset the header index.
      if (header_index >= 6) {
        header_index = 0;
      }
		}

    if (maestro.update(millis())) {
  		// Copies each Pixel's color to the NeoPixel strip
  		for (unsigned char y = 0; y < maestro.get_section(0)->get_dimensions()->y; y++) {
  			for (unsigned char x = 0; x < maestro.get_section(0)->get_dimensions()->x; x++) {
  				Colors::RGB color = maestro.get_pixel_color(0, x, y);
  				ws.set_crgb_at(x, color.r, color.g, color.b);
  			}
  		}

      ws.sync();
    }
}

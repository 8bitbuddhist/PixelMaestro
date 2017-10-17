#include <Arduino.h>
#include <PixelMaestro/core/maestro.h>
#include <WS2812.h>

using namespace PixelMaestro;

// Creates a Maestro with a single Section
Maestro maestro(8, 1);

// WS1812 stuff
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(maestro.get_section(0)->get_dimensions()->size());
cRGB RGBtoCRGB(Colors::RGB rgbColor) {
  cRGB cRGBColor;
  cRGBColor.r = rgbColor.r;
  cRGBColor.g = rgbColor.g;
  cRGBColor.b = rgbColor.b;
  return cRGBColor;
}

void setup () {
    ws.setOutput(LED_PIN);
    ws.setColorOrderGRB();

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

    for (unsigned int pixel = 0; pixel < maestro.get_section(0)->get_dimensions()->size(); pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(maestro.get_pixel_color(0, pixel)));
    }

    ws.sync();
}

#include <Arduino.h>

#include <Colors.h>
#include <Maestro.h>
#include <Pixel.h>
#include <Section.h>
#include <Show.h>
#include <show/Transition.h>
#include <show/SectionSetColorAnimationTransition.h>

#include <WS2812.h>

using namespace PixelMaestro;

const unsigned char rows = 1;
const unsigned char columns = 8;
const unsigned char numPixels = rows * columns;
const float MAX_BRIGHTNESS = 0.05;

Maestro maestro;
Pixel pixels[numPixels];
Section sections[] = {
  Section(pixels, rows, columns)
};

Show show;
const unsigned char NUM_TRANSITIONS = 1;
Transition *transitions[] = {
  new SectionSetColorAnimationTransition(5000, &sections[0], Section::ColorAnimations::NEXT, false, Section::AnimationOrientations::HORIZONTAL)
};

// WS1812 stuff
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(numPixels);
cRGB RGBtoCRGB(Colors::RGB rgbColor) {
  cRGB cRGBColor;
  cRGBColor.r = rgbColor.r * MAX_BRIGHTNESS;
  cRGBColor.g = rgbColor.g * MAX_BRIGHTNESS;
  cRGBColor.b = rgbColor.b * MAX_BRIGHTNESS;
  return cRGBColor;
}

void setup () {
    ws.setOutput(LED_PIN);
    ws.setColorOrderGRB();

    sections[0].setColors(Colors::COLORWHEEL, 12);

    maestro.setSections(sections, 1);

    show.setMaestro(&maestro);
    show.setTiming(Show::TimingModes::RELATIVE);
    show.setTransitions(transitions, NUM_TRANSITIONS);
    show.toggleLooping();
}

void loop() {
    show.update(millis());

    for (unsigned char pixel = 0; pixel < numPixels; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(sections[0].getPixelColor(pixel)));
    }

    ws.sync();
}

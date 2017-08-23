#include <Arduino.h>

#include <show.h>
#include <show/sectionsetcoloranimationevent.h>

#include <WS2812.h>

using namespace PixelMaestro;

const unsigned char ROWS = 1;
const unsigned char COLUMNS = 8;
const unsigned char NUM_PIXELS = ROWS * COLUMNS;
const float MAX_BRIGHTNESS = 0.05;

Maestro maestro;
Pixel pixels[NUM_PIXELS];
Section sections[] = {
  Section(pixels, new Point(ROWS, COLUMNS))
};

Show show;
const unsigned char NUM_EventS = 1;
Event *Events[] = {
  new SectionSetColorAnimationEvent(5000, &sections[0], Section::ColorAnimations::NEXT, false, Section::AnimationOrientations::HORIZONTAL)
};

// WS1812 stuff
const unsigned char LED_PIN = 10;
WS2812 ws = WS2812(NUM_PIXELS);
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
    show.setEvents(Events, NUM_EventS);
    show.toggleLooping();
}

void loop() {
    show.update(millis());

    for (unsigned char pixel = 0; pixel < NUM_PIXELS; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(sections[0].getPixelColor(pixel)));
    }

    ws.sync();
}

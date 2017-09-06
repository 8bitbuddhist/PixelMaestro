#include <Arduino.h>

#include <PixelMaestro/show.h>
#include <PixelMaestro/show/sectionsetcoloranimationevent.h>

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

Show show(&maestro);
const unsigned char NUM_EVENTS = 1;
Event *events[] = {
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

    sections[0].set_colors(Colors::COLORWHEEL, 12);

    maestro.set_sections(sections, 1);

    show.set_maestro(&maestro);
    show.set_timing(Show::TimingModes::RELATIVE);
    show.set_events(events, NUM_EVENTS);
    show.toggle_looping();
}

void loop() {
    show.update(millis());

    for (unsigned char pixel = 0; pixel < NUM_PIXELS; pixel++) {
      ws.set_crgb_at(pixel, RGBtoCRGB(sections[0].get_pixel_color(pixel)));
    }

    ws.sync();
}

#include <Arduino.h>
#include <WS2812.h>

#include <show.h>
#include <show/sectionsetcoloranimationevent.h>
#include <show/colorsgeneraterandomcolorevent.h>
#include <show/colorsgeneratescalingcolorarrayevent.h>

using namespace PixelMaestro;

// Single strip of 8 LEDs with 16 colors
const unsigned char ROWS = 1;
const unsigned char COLUMNS = 8;
const unsigned char NUM_PIXELS = ROWS * COLUMNS;
const unsigned char NUM_COLORS = 16;

Maestro maestro;
Pixel pixels[NUM_PIXELS];
Section sections[] = {
	Section(pixels, new Point(ROWS, COLUMNS)),
};
Colors::RGB colors[NUM_COLORS];
Colors::RGB base_color, target_color;	// These store random colors which are used to generate color schemes.

// This array stores the base colors that we'll use to generate color schemes.
const unsigned char NUM_SOURCE_COLORS = 10;
Colors::RGB source_colors[] = {
	Colors::BLACK,
	Colors::WHITE,
	{150, 0, 255},	// Deep purple
	Colors::BLUE,
	Colors::RED,
	{0, 50, 255},	// Royal blue
	Colors::GREEN,
	{255, 125, 0},	// Deep orange
	Colors::AZURE,
	{255, 0, 200}	// Pink
};

// Specify the animations that you wish to display.
const unsigned char NUM_ANIMATIONS = 5;
Section::ColorAnimations animations[] = {
	Section::ColorAnimations::SPARKLE,
	Section::ColorAnimations::WAVE,
	Section::ColorAnimations::RANDOMINDEX,
	Section::ColorAnimations::MERGE,
	Section::ColorAnimations::CYCLE
};

Show show;
const unsigned int INTERVAL = 10000;	// 10 seconds between each Event.
const unsigned char NUM_EVENTS = 4;
Event *events[] = {
	// Switch to the next animation.
	new SectionSetColorAnimationEvent(INTERVAL, &sections[0], &animations[0], NUM_ANIMATIONS, false, Section::AnimationOrientations::HORIZONTAL),
	// Select a new color scheme base color from the list of source colors.
	new ColorsGenerateRandomColorEvent(0, &base_color, source_colors, NUM_SOURCE_COLORS),
	// Select a new color scheme target color from the list of source colors.
	new ColorsGenerateRandomColorEvent(0, &target_color, source_colors, NUM_SOURCE_COLORS),
	// Create the new color scheme.
	new ColorsGenerateScalingColorArrayEvent(0, colors, &base_color, &target_color, NUM_COLORS, false)
};

// Initialize WS2812 components.
const unsigned char NUM_WS_STRIPS = 4;
WS2812 ws[] = {
	WS2812(COLUMNS),
	WS2812(COLUMNS),
	WS2812(COLUMNS),
	WS2812(COLUMNS)
};
const unsigned char WS_PINS[] = {5, 6, 9, 10};

// Set the maximum brightness of the LEDs.
const float MAX_BRIGHTNESS = 0.1;

// Convert from Colors::RGB to WS2812::cRGB
cRGB RGBtoCRGB(Colors::RGB rgbColor) {
	cRGB cRGBColor;
	cRGBColor.r = rgbColor.r * MAX_BRIGHTNESS;
	cRGBColor.g = rgbColor.g * MAX_BRIGHTNESS;
	cRGBColor.b = rgbColor.b * MAX_BRIGHTNESS;
	return cRGBColor;
}

void setup () {
	// Initialize the WS2812 LED strips.
	for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
		ws[strip].setOutput(WS_PINS[strip]);
		ws[strip].setColorOrderGRB();
	}

	// Set the initial color array to all black.
	Colors::generate_scaling_color_array(colors, &Colors::BLACK, &Colors::BLACK, COLUMNS, false);
	sections[0].set_colors(colors, NUM_COLORS);
	sections[0].set_cycle_interval(100);
	sections[0].toggle_fade();

	maestro.set_sections(sections, 1);

	// Initialize the Show.
	show.set_maestro(&maestro);
	show.set_timing(Show::TimingModes::RELATIVE);
	show.set_events(events, NUM_EVENTS);
	show.toggle_looping();
}

void loop() {
	show.update(millis());

	// For each Pixel, set the corresponding WS2812 pixel to the Pixel's color.
	for (unsigned char pixel = 0; pixel < NUM_PIXELS; pixel++) {
		for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
			ws[strip].set_crgb_at(pixel, RGBtoCRGB(sections[0].get_pixel_color(pixel)));
		}
	}

	// Update each WS2812 strip.
	for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
		ws[strip].sync();
	}
}

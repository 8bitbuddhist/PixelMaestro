#include <Arduino.h>

#include <Colors.h>
#include <Maestro.h>
#include <Pixel.h>
#include <Section.h>
#include <Show.h>
#include <show/Event.h>
#include <show/SectionSetColorAnimationEvent.h>
#include <show/ColorsGenerateRandomColorEvent.h>
#include <show/ColorsGenerateScalingColorArrayEvent.h>

#include <WS2812.h>

using namespace PixelMaestro;

// Single strip of 8 LEDs with 16 colors
const unsigned char ROWS = 1;
const unsigned char COLUMNS = 8;
const unsigned char NUM_PIXELS = ROWS * COLUMNS;
const unsigned char NUM_COLORS = 16;

Maestro maestro;
Pixel pixels[NUM_PIXELS];
Section sections[] = {
	Section(pixels, ROWS, COLUMNS),
};
Colors::RGB colors[NUM_COLORS];
Colors::RGB baseColor, targetColor;	// These store random colors which are used to generate color schemes.

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
const unsigned char NUM_EventS = 4;
Event *Events[] = {
	// Switch to the next animation.
	new SectionSetColorAnimationEvent(INTERVAL, &sections[0], &animations[0], NUM_ANIMATIONS, false, Section::AnimationOrientations::HORIZONTAL),
	// Select a new color scheme base color from the list of source colors.
	new ColorsGenerateRandomColorEvent(0, &baseColor, source_colors, NUM_SOURCE_COLORS),
	// Select a new color scheme target color from the list of source colors.
	new ColorsGenerateRandomColorEvent(0, &targetColor, source_colors, NUM_SOURCE_COLORS),
	// Create the new color scheme.
	new ColorsGenerateScalingColorArrayEvent(0, colors, &baseColor, &targetColor, NUM_COLORS, false),
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
	// Due to wiring issues, sleep for 15 seconds to prevent powering LEDs over USB
	delay(15000);

	// Initialize the WS2812 LED strips.
	for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
		ws[strip].setOutput(WS_PINS[strip]);
		ws[strip].setColorOrderGRB();
	}

	// Set the initial color array to all black.
	Colors::generateScalingColorArray(colors, &Colors::BLACK, &Colors::BLACK, COLUMNS, false);
	sections[0].setColors(colors, NUM_COLORS);

	maestro.setSections(sections, 1);

	// Initialize the Show.
	show.setMaestro(&maestro);
	show.setTiming(Show::TimingModes::RELATIVE);
	show.setEvents(Events, NUM_EventS);
	show.toggleLooping();
}

void loop() {
	show.update(millis());

	// For each Pixel, set the corresponding WS2812 pixel to the Pixel's color.
	for (unsigned char pixel = 0; pixel < NUM_PIXELS; pixel++) {
		for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
			ws[strip].set_crgb_at(pixel, RGBtoCRGB(sections[0].getPixelColor(pixel)));
		}
	}

	// Update each WS2812 strip.
	for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
		ws[strip].sync();
	}
}

#include <Arduino.h>
#include <WS2812.h>

#include <PixelMaestro/core/maestro.h>

#include <PixelMaestro/animation/cycleanimation.h>
#include <PixelMaestro/animation/mergeanimation.h>
#include <PixelMaestro/animation/randomanimation.h>
#include <PixelMaestro/animation/sparkleanimation.h>
#include <PixelMaestro/animation/waveanimation.h>

#include <PixelMaestro/show/show.h>
#include <PixelMaestro/show/sectionsetanimationevent.h>
#include <PixelMaestro/show/colorsgeneraterandomcolorevent.h>
#include <PixelMaestro/show/colorsgeneratescalingcolorarrayevent.h>

using namespace PixelMaestro;

// Single strip of 8 LEDs with 16 colors
const unsigned char ROWS = 1;
const unsigned char COLUMNS = 8;
const unsigned char NUM_COLORS = 16;

// This declares the number of Pixels used, assigns them to a Section, then assigns that Section to a Maestro.
Section sections[] = {
	Section(new Point(ROWS, COLUMNS)),
};
Maestro maestro(sections, 1);

Colors::RGB colors[NUM_COLORS] = {Colors::BLACK};	// Stores the color array used by the Section.
Colors::RGB base_color, target_color;							// These store random colors which are used to generate color palettes for the colors array.

// Stores the base colors that we'll use to generate color palettes.
const unsigned char NUM_SOURCE_COLORS = 10;
Colors::RGB source_colors[] = {
	Colors::BLACK,
	Colors::WHITE,
	{150, 0, 255},	// Deep purple
	Colors::BLUE,
	Colors::RED,
	{0, 50, 255},		// Royal blue
	Colors::GREEN,
	{255, 125, 0},	// Deep orange
	Colors::AZURE,
	{255, 0, 200}		// Pink
};

// Initializes the animations that the Section will cycle through.
const unsigned char NUM_ANIMATIONS = 5;
Animation* animations[] = {
	new SparkleAnimation(colors, NUM_SOURCE_COLORS),
	new WaveAnimation(colors, NUM_SOURCE_COLORS),
	new RandomAnimation(colors, NUM_SOURCE_COLORS),
	new MergeAnimation(colors, NUM_SOURCE_COLORS),
	new CycleAnimation(colors, NUM_SOURCE_COLORS)
};

// Initializes the Show.
const unsigned int INTERVAL = 10000;	// 10 seconds between each animation.
const unsigned char NUM_EVENTS = 4;		// 4 events total (declared in the events array below).
Event *events[] = {
	// Switches to the next animation in the list.
	new SectionSetAnimationEvent(INTERVAL, &sections[0], &animations[0], NUM_ANIMATIONS, true),
	// Selects a new base color from the list of source colors.
	new ColorsGenerateRandomColorEvent(0, &base_color, source_colors, NUM_SOURCE_COLORS),
	// Selects a new target color from the list of source colors.
	new ColorsGenerateRandomColorEvent(0, &target_color, source_colors, NUM_SOURCE_COLORS),
	// Generates a new color scheme using the base and target colors.
	new ColorsGenerateScalingColorArrayEvent(0, colors, &base_color, &target_color, NUM_COLORS, false)
};
Show show(&maestro, events, NUM_EVENTS);

// Initialize WS2812 components.
const unsigned char WS_PINS[] = {5, 6, 9, 10};
const unsigned char NUM_WS_STRIPS = 4;
WS2812 ws[] = {
	WS2812(ROWS * COLUMNS),
	WS2812(ROWS * COLUMNS),
	WS2812(ROWS * COLUMNS),
	WS2812(ROWS * COLUMNS)
};

// Convert from Colors::RGB to WS2812::cRGB
cRGB RGBtoCRGB(Colors::RGB rgbColor) {
	cRGB cRGBColor;
	cRGBColor.r = rgbColor.r;
	cRGBColor.g = rgbColor.g;
	cRGBColor.b = rgbColor.b;
	return cRGBColor;
}

void setup () {
	// Initialize the WS2812 LED strips.
	for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
		ws[strip].setOutput(WS_PINS[strip]);
		ws[strip].setColorOrderGRB();
	}

	// Sets the Section's cycle interval to 100ms and the brightness to 10%
	maestro.get_section(0)->set_cycle_interval(100);
	maestro.set_brightness(0.1);

	// Loop the show every INTERVAL
	show.set_timing(Show::TimingModes::RELATIVE);
	show.set_looping(true);
}

void loop() {
	show.update(millis());

	// For each Pixel, set the corresponding WS2812 pixel to the Pixel's color.
	for (unsigned char pixel = 0; pixel < ROWS * COLUMNS; pixel++) {
		for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
			ws[strip].set_crgb_at(pixel, RGBtoCRGB(maestro.get_pixel_color(0, pixel)));
		}
	}

	// Update each WS2812 strip.
	for (unsigned char strip = 0; strip < NUM_WS_STRIPS; strip++) {
		ws[strip].sync();
	}
}

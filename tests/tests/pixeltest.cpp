#include "../catch/single_include/catch.hpp"
#include "../../src/colorpresets.h"
#include "../../src/core/colors.h"
#include "../../src/core/pixel.h"
#include "pixeltest.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Pixel.", "[Pixel]") {
	Pixel pixel;
	unsigned short interval = 100;
	unsigned short refresh_rate = 10;
	Colors::RGB red = ColorPresets::Red;
	bool fade = true;

	SECTION("Set a new color.") {
		pixel.set_next_color(red, 1);
		pixel.update();
		REQUIRE(pixel.get_color() == ColorPresets::Red);
	}

	SECTION("Test positive fading.") {
		// Calculate the step_count between the refresh and cycle rates
		uint8_t step_count = (uint8_t)(interval / (float)refresh_rate);

		// Change to red, allow fading, finish a transition every 10 ms
		pixel.set_next_color(red, step_count);

		// Update the Pixel
		pixel.update();

		Colors::RGB current_color = pixel.get_color();
		REQUIRE(current_color.r == (red.r / step_count));
		REQUIRE(current_color.g == 0);
		REQUIRE(current_color.b == 0);
	}

	SECTION("Test negative fading.") {
		uint8_t step_count = (uint8_t)(interval / (float)refresh_rate);
		Colors::RGB white = ColorPresets::White;

		pixel.set_next_color(white, 1);
		pixel.update(true);
		pixel.set_next_color(ColorPresets::Black, step_count);
		pixel.update();

		uint8_t step = (ColorPresets::Black.r - white.r) / (float)step_count;

		Colors::RGB current_color = pixel.get_color();
		uint8_t target_color_val = ColorPresets::White.r + step;
		REQUIRE(current_color.r == target_color_val);
		REQUIRE(current_color.g == target_color_val);
		REQUIRE(current_color.b == target_color_val);
	}
}

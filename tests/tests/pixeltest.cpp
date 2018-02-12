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
		pixel.set_next_color(&red, 0);
		pixel.update();
		REQUIRE(*pixel.get_color() == ColorPresets::Red);
	}

	// Calculate the step_count between the refresh and cycle rates
	unsigned short step_count = (unsigned short)(interval / (float)refresh_rate);

	// Change to red, allow fading, finish a transition every 10 ms
	pixel.set_next_color(&red, step_count);

	// Update the Pixel
	pixel.update();

	SECTION("Update and check the current color.") {
		Colors::RGB current_color = *pixel.get_color();
		REQUIRE(current_color.r == (red.r > 0 ? red.r / step_count : 0));
		REQUIRE(current_color.g == (red.g > 0 ? red.g / step_count : 0));
		REQUIRE(current_color.b == (red.b > 0 ? red.b / step_count : 0));
	}
}

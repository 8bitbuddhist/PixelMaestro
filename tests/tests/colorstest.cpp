#define CATCH_CONFIG_MAIN
#include "../catch/single_include/catch.hpp"
#include "../../src/colorpresets.h"
#include "colorstest.h"

using namespace PixelMaestro;

TEST_CASE("Color values are stored correctly.", "[Colors::RGB]") {
	Colors::RGB red = ColorPresets::Red;

	REQUIRE(red.r == 255);
	REQUIRE(red.g == 0);
	REQUIRE(red.b == 0);
}

TEST_CASE("Color comparison works.", "[Colors::RGB]") {
	Colors::RGB orange = ColorPresets::Orange;
	Colors::RGB azure = ColorPresets::Azure;
	Colors::RGB also_orange = orange;

	REQUIRE(orange != azure);
	REQUIRE(orange == also_orange);

	SECTION("Changing also_orange causes the colors to no longer match.") {
		also_orange.g = 101;
		REQUIRE(orange != also_orange);
	}
}

TEST_CASE("Can generate random color.", "[Colors::RGB]") {
	Colors::RGB new_color = Colors::generate_random_color();

	// Verify that at least one of the values is non-zero
	REQUIRE(new_color.r + new_color.g + new_color.b > 0);
}

TEST_CASE("Can generate random color array.", "[Array]") {
	unsigned char num_colors = 10;
	Colors::RGB new_array[num_colors];

	Colors::generate_random_color_array(new_array, num_colors);

	// There's a (very) small chance that black could have been randomly generated, but we'll assume it wasn't.
	for (unsigned char index = 0; index < num_colors; index++) {
		REQUIRE(new_array[index].r + new_array[index].g + new_array[index].b != 0);
	}
}

TEST_CASE("Can generate scaling color array.", "[Array]") {
	unsigned char num_colors = 15;
	unsigned char threshold = 255 / num_colors;
	Colors::RGB new_array[num_colors];

	Colors::generate_scaling_color_array(new_array, &ColorPresets::Black, &ColorPresets::White, num_colors, false);

	unsigned char expected = 0;
	for (unsigned char index = 0; index < num_colors; index++) {
		REQUIRE((unsigned int)new_array[index].r == expected);
		REQUIRE((unsigned int)new_array[index].g == expected);
		REQUIRE((unsigned int)new_array[index].b == expected);

		expected += threshold;
	}
}

TEST_CASE("Can mix colors.", "[Colors::RGB]") {

	SECTION("Alpha blend reduces color 2 by specified amount.") {
		Colors::RGB mixed = Colors::mix_colors(ColorPresets::Black, ColorPresets::White, Colors::MixMode::Alpha, 51);
		Colors::RGB target = {51, 51, 51};
		REQUIRE(mixed == target);
	}

	SECTION("Multiply mix mode multiplies color by half.") {
		Colors::RGB color = {254, 128, 76};
		Colors::RGB half_white = {128, 128, 128};
		Colors::RGB mixed = Colors::mix_colors(color, half_white, Colors::MixMode::Multiply);

		Colors::RGB half_color = color * 0.5;
		REQUIRE((unsigned int)mixed.r == (unsigned int)half_color.r);
		REQUIRE((unsigned int)mixed.g == (unsigned int)half_color.g);
		REQUIRE((unsigned int)mixed.b == (unsigned int)half_color.b);
	}

	SECTION("Overlay mix mode shows color 2 unless color 2 is black.") {
		REQUIRE(Colors::mix_colors(ColorPresets::Red, ColorPresets::Blue, Colors::MixMode::Overlay) == ColorPresets::Blue);
		REQUIRE(Colors::mix_colors(ColorPresets::Red, ColorPresets::Black, Colors::MixMode::Overlay) == ColorPresets::Red);
	}
}

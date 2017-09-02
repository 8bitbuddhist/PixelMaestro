#define CATCH_CONFIG_MAIN
#include "../catch/single_include/catch.hpp"
#include "colors.h"
#include "colorstest.h"

using namespace PixelMaestro;

TEST_CASE("Color values are stored correctly.", "[Colors::RGB]") {
    Colors::RGB red = Colors::RED;

    REQUIRE(red.r == 255);
    REQUIRE(red.g == 0);
    REQUIRE(red.b == 0);
}

TEST_CASE("Color comparison works.", "[Colors::RGB]") {
    Colors::RGB color1 = Colors::ORANGE;
    Colors::RGB color2 = Colors::AZURE;
    Colors::RGB color3 = color1;

    REQUIRE(color1 != color2);
    REQUIRE(color1 == color3);

    SECTION("Changing color3 causes the colors to no longer match.") {
        color3.g = 101;
        REQUIRE(color1 != color3);
    }
}

TEST_CASE("Can generate random color.", "[Colors::RGB]") {
	Colors::RGB newColor = {0, 0, 0};
	newColor = Colors::generate_random_color();
	
	// Verify that at least one of the values is non-zero
	REQUIRE(newColor.r + newColor.g + newColor.b > 0);
}

TEST_CASE("Can generate random color array.", "[Array]") {
    unsigned char numColors = 10;
    unsigned char range = 10;
    Colors::RGB newArray[numColors];

    Colors::generate_random_color_array(newArray, &Colors::BLUE, numColors, range);

	// Ensure non-zero value for blue. There's a non-zero chance blue was randomly set to 0, but it's unlikely.
    for (unsigned char index = 0; index < numColors; index++) {
        REQUIRE(newArray[index].r == 0);
        REQUIRE(newArray[index].g == 0);
		REQUIRE(newArray[index].b != 0);
    }
}

TEST_CASE("Can generate scaling color array.", "[Array]") {
	unsigned char numColors = 15;
	unsigned char threshold = 255 / numColors;
	Colors::RGB newArray[numColors];

	Colors::generate_scaling_color_array(newArray, &Colors::BLACK, &Colors::WHITE, numColors, false);

	unsigned char expected = 0;
	for (unsigned char index = 0; index < numColors; index++) {
		REQUIRE((unsigned int)newArray[index].r == expected);
		REQUIRE((unsigned int)newArray[index].g == expected);
		REQUIRE((unsigned int)newArray[index].b == expected);

		expected += threshold;
	}
}

TEST_CASE("Can mix colors.", "[Colors::RGB]") {

    SECTION("Normal blending red and blue results in purple.") {
        Colors::RGB purple = Colors::mix_colors(&Colors::RED, &Colors::BLUE, Colors::MixMode::NORMAL, 0.5);
        REQUIRE(purple.r == 127);
        REQUIRE(purple.g == 0);
        REQUIRE(purple.b == 127);
    }

    SECTION("Color multiplied by half equals halved values.") {
		Colors::RGB color = {254, 128, 76};
		Colors::RGB halfWhite = {128, 128, 128};
		Colors::RGB mixed = Colors::mix_colors(&color, &halfWhite, Colors::MixMode::MULTIPLY);
		
		Colors::RGB halfColor = color / 2;
		REQUIRE((unsigned int)mixed.r == (unsigned int)halfColor.r);
		REQUIRE((unsigned int)mixed.g == (unsigned int)halfColor.g);
		REQUIRE((unsigned int)mixed.b == (unsigned int)halfColor.b);
	}
	
	SECTION("Colors blend with specified alpha.") {
		Colors::RGB mixed = Colors::mix_colors(&Colors::BLACK, &Colors::WHITE, Colors::MixMode::ALPHA_BLENDING, 0.2);
		Colors::RGB target = {51, 51, 51};
		REQUIRE(mixed == target);
	}
}

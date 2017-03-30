#define CATCH_CONFIG_MAIN
#include "../catch/include/catch.hpp"
#include "ColorsTest.h"
#include "../Colors.h"

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

/*
TEST_CASE("HSVs are successfully converted to RGBs.", "[Colors::RGB]") {
    unsigned int hue = 180;
    unsigned int sat = 100;
    unsigned int val = 100;

    Colors::RGB cyan = Colors::HSVtoRGB(hue, sat, val);

    REQUIRE(Colors::colorsMatch(&cyan, &Colors::CYAN) == true);
}
*/

TEST_CASE("Can generate random color array.", "[Array]") {
    unsigned char numColors = 10;
    Colors::RGB newArray[numColors];

    Colors::generateRandomColorArray(newArray, Colors::BLUE, numColors, 10);

    // TODO: Validate resulting color array.
}

TEST_CASE("Can mix colors.", "[Colors::RGB]") {

    SECTION("Normal blending red and blue results in purple.") {
        Colors::RGB purple = Colors::mixColors(&Colors::RED, &Colors::BLUE, Colors::MixMode::NORMAL, 0.5);
        REQUIRE(purple.r == 127);
        REQUIRE(purple.g == 0);
        REQUIRE(purple.b == 127);
    }

    // TODO: Alpha blending
}

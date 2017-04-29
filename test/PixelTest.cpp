#include "../include/catch/include/catch.hpp"
#include "PixelTest.h"
#include "../include/Pixel.h"
#include "../include/Colors.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Pixel.", "[Pixel]") {
    Pixel pixel;
    unsigned short cycleSpeed = 100;
    unsigned short refreshRate = 10;
    Colors::RGB color = Colors::RED;
    bool fade = true;

    SECTION("Set a new color.") {
        pixel.setNextColor(&color, false, 0, 0);
        pixel.update();
        REQUIRE(*pixel.getColor() == Colors::RED);
    }

    // Change to red, allow fading, finish a transition every 10 ms
    pixel.setNextColor(&color, fade, cycleSpeed, refreshRate);

    // Calculate the diff between the refresh and cycle rates
    unsigned short diff = (unsigned short)(cycleSpeed / (float)refreshRate);

    SECTION("Get the step count. It should equal the cycle speed and refresh rate we set in the previous section.") {
        REQUIRE(pixel.getStepCount() == diff);
    }

    // Update the Pixel
    pixel.update();

    SECTION("Update and check the current color.") {
        Colors::RGB currentColor = *pixel.getColor();
        REQUIRE(currentColor.r == (color.r > 0 ? color.r / diff : 0));
        REQUIRE(currentColor.g == (color.g > 0 ? color.g / diff : 0));
        REQUIRE(currentColor.b == (color.b > 0 ? color.b / diff : 0));
    }
}

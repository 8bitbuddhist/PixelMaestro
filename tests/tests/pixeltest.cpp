#include "../catch/single_include/catch.hpp"
#include "../../src/core/colors.h"
#include "../../src/core/pixel.h"
#include "pixeltest.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Pixel.", "[Pixel]") {
    Pixel pixel;
    unsigned short cycleSpeed = 100;
    unsigned short refreshRate = 10;
    Colors::RGB color = Colors::RED;
    bool fade = true;

    SECTION("Set a new color.") {
        pixel.set_next_color(&color, false, 0, 0);
        pixel.update();
        REQUIRE(*pixel.get_color() == Colors::RED);
    }

    // Change to red, allow fading, finish a transition every 10 ms
    pixel.set_next_color(&color, fade, cycleSpeed, refreshRate);

    // Calculate the diff between the refresh and cycle rates
    unsigned short diff = (unsigned short)(cycleSpeed / (float)refreshRate);

    // Update the Pixel
    pixel.update();

    SECTION("Update and check the current color.") {
        Colors::RGB currentColor = *pixel.get_color();
        REQUIRE(currentColor.r == (color.r > 0 ? color.r / diff : 0));
        REQUIRE(currentColor.g == (color.g > 0 ? color.g / diff : 0));
        REQUIRE(currentColor.b == (color.b > 0 ? color.b / diff : 0));
    }
}

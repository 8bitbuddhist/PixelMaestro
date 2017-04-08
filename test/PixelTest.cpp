#include "../include/catch/include/catch.hpp"
#include "PixelTest.h"
#include "../Pixel.h"
#include "../Colors.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Pixel.", "[Pixel]") {
    Pixel pixel;
    unsigned char interval = 10;
    Colors::RGB color = Colors::RED;
    bool fade = true;

    // Change to red, allow fading, finish a transition every 10 ms
    pixel.setNextColor(&color, fade, interval);

    SECTION("Set a new color.") {
        REQUIRE(*pixel.getNextColor() == Colors::RED);
    }

    SECTION("Get the step count. It should equal the interval we set in the previous section.") {
        REQUIRE(pixel.getStepCount() == interval);
    }

    // Update the Pixel
    pixel.update(fade);

    SECTION("Update and check the current color.") {
        Colors::RGB currentColor = *pixel.getColor();
        REQUIRE(currentColor.r == (color.r > 0 ? color.r / interval : 0));
        REQUIRE(currentColor.g == (color.g > 0 ? color.g / interval : 0));
        REQUIRE(currentColor.b == (color.b > 0 ? color.b / interval : 0));
    }
}

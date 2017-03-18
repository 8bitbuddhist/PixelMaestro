#include "catch.hpp"
#include "LineTest.h"
#include "../Line.h"
#include "../Colors.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Line of Pixels.", "[Line]") {
    const unsigned char numPixels = 10;
    Pixel pixels[numPixels];
    Line *line = new Line(pixels, numPixels);

    SECTION("Test basic Pixel interaction.") {
        const unsigned char pixelIndex = 0;
        Pixel *pixel = line->getPixel(pixelIndex);

        REQUIRE(line->getNumPixels() == numPixels);

        REQUIRE(Colors::colorsMatch(pixel->getColor(), &Colors::BLACK));

        // Set the color of Pixels to Azure.
        line->setOne(pixelIndex, &Colors::AZURE);
        REQUIRE(Colors::colorsMatch(pixel->getNextColor(), &Colors::AZURE));

        line->setAll(&Colors::GREEN);
        for (int index = 0; index < numPixels; index++) {
            REQUIRE(Colors::colorsMatch(line->getPixel(index)->getNextColor(), &Colors::GREEN));
        }
    }

    SECTION("Test speed and fade.") {
        REQUIRE(line->getFade() == true);

        line->setUpdateSpeed(10);
        REQUIRE(line->getUpdateSpeed() == 10);

        line->toggleFade();
        REQUIRE(line->getFade() == false);
        REQUIRE(line->getUpdateSpeed() == 100);

        line->setUpdateSpeed(5);
        REQUIRE(line->getUpdateSpeed() == 25);
    }

    SECTION("Test color animations.") {
        const unsigned char numColors = 10;
        Colors::RGB colors[numColors] = {
            Colors::AZURE,
            Colors::BLACK,
            Colors::BLUE,
            Colors::CHARTREUSE,
            Colors::CYAN,
            Colors::GREEN,
            Colors::INDIGO,
            Colors::MAGENTA,
            Colors::ORANGE,
            Colors::RED};
        line->setColors(colors, numColors);
        line->setColorAnimation(Line::ColorAnimations::BLINK);
        line->toggleFade();

        // Set an instant update speed
        line->setUpdateSpeed(0);

        // Verify that all colors match
        line->update(0);
        for (int index = 0; index < numPixels; index++) {
            REQUIRE(Colors::colorsMatch(line->getPixel(index)->getColor(), &colors[index]));
        }

        // Blink to black, then re-check colors
        line->update(0);
        for (int index = 0; index < numPixels; index++) {
            REQUIRE(Colors::colorsMatch(line->getPixel(index)->getColor(), &Colors::BLACK));
        }
    }
}

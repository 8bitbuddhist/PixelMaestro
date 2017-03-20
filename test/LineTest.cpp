#include "catch.hpp"
#include "LineTest.h"
#include "../Line.h"
#include "../Colors.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Line of Pixels.", "[Line]") {
    const unsigned char numPixels = 10;
    const unsigned char numColors = 10;
    Pixel pixels[numPixels];
    Line *line = new Line(pixels, numPixels);
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
        Colors::RED
    };

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

    // START color animation testing
    // Set the colors and an instantaneous update speed.
    line->setColors(colors, numColors);
    line->setUpdateSpeed(0);

    SECTION("Test SOLID animation.") {
        line->setColorAnimation(Line::ColorAnimations::SOLID);
        line->update(0);
        for (int index = 0; index < numColors; index++) {
            REQUIRE(Colors::colorsMatch(line->getPixel(index)->getColor(), &colors[index]));
        }
    }

    SECTION("Test BLINK animation.") {
        line->setColorAnimation(Line::ColorAnimations::BLINK);
        line->update(0);
        for (int index = 0; index < numColors; index++) {
            REQUIRE(Colors::colorsMatch(line->getPixel(index)->getColor(), &colors[index]));
        }

        line->update(0);
        for (int index = 0; index < numColors; index++) {
            REQUIRE(Colors::colorsMatch(line->getPixel(index)->getColor(), &Colors::BLACK));
        }
    }

    SECTION("Test WAVE animation.") {
        line->setColorAnimation(Line::ColorAnimations::WAVE);
        for (int colorIndex = 0; colorIndex < numColors; colorIndex++) {
            line->update(0);
            REQUIRE(Colors::colorsMatch(line->getPixel(0)->getColor(), &colors[colorIndex]));
        }

        // TODO: Test reverse
    }

    SECTION("Test PONG animation.") {
        line->setColorAnimation(Line::ColorAnimations::PONG);
        for (int index = 0; index < 20; index++) {
            line->update(0);
            if (index <= numColors - 1) {
                REQUIRE(Colors::colorsMatch(line->getPixel(0)->getColor(), &colors[index]));
            }
            else {
                REQUIRE(Colors::colorsMatch(line->getPixel(0)->getColor(), &colors[(numColors - (index - numColors)) - 2]));
            }
        }
    }

    // TODO: Test MERGE
    // TODO: Test RANDOMINDEX
    // TODO: Test SPARKLE
    // TODO: Test PATTERN

    SECTION("Test CYCLE animation.") {
        line->setColorAnimation(Line::ColorAnimations::CYCLE);
        // Verify that all colors match
        for (int colorIndex = 0; colorIndex < numColors; colorIndex++) {
            line->update(0);
            for (int pixelIndex = 0; pixelIndex < numPixels; pixelIndex++) {
                REQUIRE(Colors::colorsMatch(line->getPixel(pixelIndex)->getColor(), &colors[colorIndex]));
            }
        }

        // TODO: Test reverse
    }

    // TODO: Test STATIC

    // END color animation testing
}

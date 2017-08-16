#include "../catch/single_include/catch.hpp"
#include "Colors.h"
#include "Section.h"
#include "SectionTest.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Section.", "[Section]") {
	Section::Layout layout = {1, 12};
	Pixel pixels[layout.rows * layout.columns];
	Section section(pixels, layout.rows, layout.columns);
	
	int testPixelIndex = 11;
	
	SECTION("Verify that Pixels are set correctly.") {
		REQUIRE(section.getPixel(testPixelIndex) == &pixels[testPixelIndex]);
		REQUIRE(section.getNumPixels() == layout.rows * layout.columns);
		REQUIRE(section.getLayout()->rows == layout.rows);
		REQUIRE(section.getLayout()->columns == layout.columns);
	}
	
	SECTION("Verify that Animations and Colors are set correctly.") {
		section.setColorAnimation(Section::ColorAnimations::SOLID, false);
		section.setColors(Colors::COLORWHEEL, 12);
		section.setCycleInterval(1000);
		
		// Disable fading
		if (section.getFade()) {
			section.toggleFade();
		}
		section.update(1000);
		
		Colors::RGB pixelColor = section.getPixelColor(testPixelIndex);
		Colors::RGB targetColor = Colors::COLORWHEEL[testPixelIndex];

		REQUIRE((int)pixelColor.r == (int)targetColor.r);
		REQUIRE((int)pixelColor.g == (int)targetColor.g);
		REQUIRE((int)pixelColor.b == (int)targetColor.b);
	}
}

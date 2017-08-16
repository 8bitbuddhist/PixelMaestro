#include "../catch/single_include/catch.hpp"
#include "Colors.h"
#include "Section.h"
#include "SectionTest.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Section.", "[Section]") {
	Section::Layout layout = {1, 12};
	Pixel pixels[layout.rows * layout.columns];
	Section section(pixels, layout.rows, layout.columns);
	
	SECTION("Verify that Pixels are set correctly.") {
		REQUIRE(section.getPixel(11) == &pixels[11]);
	}
	
	SECTION("Verify that Animations and Colors are set correctly.") {
		section.setColorAnimation(Section::ColorAnimations::SOLID, false);
		
		section.setColors(Colors::COLORWHEEL, 12);
		if (section.getFade()) {
			section.toggleFade();
		}
		section.update(1000);
		
		Colors::RGB pixelColor = section.getPixelColor(11);
		Colors::RGB targetColor = Colors::COLORWHEEL[11];

		REQUIRE((int)pixelColor.r == (int)targetColor.r);
		REQUIRE((int)pixelColor.g == (int)targetColor.g);
		REQUIRE((int)pixelColor.b == (int)targetColor.b);
	}
}

#include "../catch/single_include/catch.hpp"
#include "colors.h"
#include "point.h"
#include "section.h"
#include "sectiontest.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a section->", "[Section]") {
	Point *layout = new Point(1, 12);
	Pixel pixels[layout->x * layout->y];
	Section *section = new Section(&pixels[0], layout);
	
	int testPixelIndex = 11;
	
	SECTION("Verify that Pixels are set correctly.") {
		REQUIRE(section->get_pixel(testPixelIndex) == &pixels[testPixelIndex]);
		REQUIRE(section->get_num_pixels() == (layout->x * layout->y));
		REQUIRE(section->get_dimensions()->x == layout->x);
		REQUIRE(section->get_dimensions()->y == layout->y);
	}
	
	SECTION("Verify that Animations and Colors are set correctly.") {
		section->set_color_animation(Section::ColorAnimations::SOLID, false);
		section->set_colors(Colors::COLORWHEEL, 12);
		section->set_cycle_interval(100);
		
		// Disable fading
		if (section->get_fade()) {
			section->toggle_fade();
		}
		section->update(101);
		
		Colors::RGB pixelColor = section->get_pixel_color(testPixelIndex);
		Colors::RGB targetColor = Colors::COLORWHEEL[testPixelIndex];

		REQUIRE((int)pixelColor.r == (int)targetColor.r);
		REQUIRE((int)pixelColor.g == (int)targetColor.g);
		REQUIRE((int)pixelColor.b == (int)targetColor.b);
	}
}

#include "../catch/single_include/catch.hpp"
#include "../../src/animation/solidanimation.h"
#include "../../src/animation/cycleanimation.h"
#include "../../src/core/maestro.h"
#include "../../src/core/section.h"
#include "../../src/colorpresets.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Mastro.", "[Maestro]") {
	Point s1_point(10, 10);
	Point s2_point(20, 20);

	Section sections[] = {
	  Section(s1_point.x, s1_point.y),
	  Section(s2_point.x, s2_point.y)
	};
	Maestro maestro(sections, 2);

	SECTION("Get Maestro Sections.") {
		Section* s1 = maestro.get_section(0);
		REQUIRE(*s1->get_dimensions() == s1_point);

		Section* s2 = maestro.get_section(1);
		REQUIRE(*s2->get_dimensions() == s2_point);
	}

	SECTION("Verify update works.") {
		Section* s1 = maestro.get_section(0);
		s1->set_one(0, 0, &ColorPresets::White);

		// Try without forcing a refresh
		REQUIRE(maestro.update(0, false) == false);

		// Force refresh
		REQUIRE(maestro.update(0, true) == true);
		REQUIRE(maestro.get_pixel_color(0, 0, 0) == ColorPresets::White);
	}

	SECTION("Verify global brightness works.") {
		maestro.set_brightness(0);
		maestro.update(0, true);

		REQUIRE(maestro.get_pixel_color(0, 0, 0) == ColorPresets::Black);
	}

}

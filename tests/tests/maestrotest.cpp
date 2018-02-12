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
	  Section(s1_point),
	  Section(s2_point)
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
		Animation* animation = s1->set_animation(AnimationType::Solid, ColorPresets::Colorwheel, 12);
		animation->set_timer(100);
		animation->set_fade(false);

		maestro.update(101);

		REQUIRE(*s1->get_pixel(0, 0)->get_color() == ColorPresets::Colorwheel[0]);
	}

	SECTION("Verify global brightness works.") {
		Section* s1 = maestro.get_section(0);
		Animation* animation = s1->set_animation(AnimationType::Solid, ColorPresets::Colorwheel, 12);
		animation->set_timer(100);
		animation->set_fade(false);

		maestro.set_brightness(127);
		maestro.update(101);

		REQUIRE(maestro.get_pixel_color(0, 0, 0) == (ColorPresets::Colorwheel[0] * 0.5));
	}

	SECTION("Verify running state works.") {
		Section* s1 = maestro.get_section(0);
		s1->set_animation(AnimationType::Solid, ColorPresets::Colorwheel, 12);

		maestro.get_timer()->stop();

		// Run a few updates
		for (unsigned char i = 0; i < 5; i++) {
			maestro.update(100 * i);
		}

		REQUIRE(*s1->get_pixel(0, 0)->get_color() == ColorPresets::Black);
	}

}

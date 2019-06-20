#include "../catch/single_include/catch.hpp"
#include "../../src/cue/show.h"
#include "../../src/cue/sectioncuehandler.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Show.", "[Show]") {
	Section sections[] = {
		Section(10, 10)
	};

	Maestro maestro(sections, 1);
	Show& show = maestro.set_show(nullptr, 0);

	CueController* controller = &maestro.get_cue_controller();
	SectionCueHandler& section_handler = dynamic_cast<SectionCueHandler&>(controller->enable_section_cue_handler());

	SECTION("Verify Events can be created.") {
		int time = 1000;
		uint8_t* cue = section_handler.set_animation(0, 0, AnimationType::Solid);
		Event event = Event(time, cue);

		REQUIRE(event.get_time() == time);

		for (uint32_t index = 0; index < controller->get_cue_size(cue); index++) {
			REQUIRE(cue[index] == event.get_cue()[index]);
		}
	}

	SECTION("Verify Events can be assigned to a Show.") {
		Event events[] = {
			Event(1000, section_handler.set_animation(0, 0, AnimationType::Solid))
		};
		show.set_events(events, 1);

		REQUIRE(show.get_events() == events);
		REQUIRE(show.get_num_events() == 1);
	}

	SECTION("Verify Event processing works.") {
		Event events[] = {
			Event(0, section_handler.set_animation(0, 0, AnimationType::Solid)),
			Event(2, section_handler.set_animation(0, 0, AnimationType::Solid))
		};
		show.set_events(events, 2);
		show.update(0);

		REQUIRE(show.get_current_index() == 1);
		REQUIRE(show.get_last_time() == 0);
	}
}

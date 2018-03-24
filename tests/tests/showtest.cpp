#include "../catch/single_include/catch.hpp"
#include "../../src/cue/show.h"
#include "../../src/cue/sectioncuehandler.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Show.", "[Show]") {
	Maestro maestro(10, 10);
	Show* show = maestro.set_show(nullptr, 0);

	SECTION("Verify Show is initialized.") {
		REQUIRE(show != nullptr);
		REQUIRE(maestro.get_show() == show);
		REQUIRE(maestro.get_cue_controller() != nullptr);
	}

	CueController* controller = maestro.get_cue_controller();
	SectionCueHandler* section_handler = static_cast<SectionCueHandler*>(controller->enable_handler(CueController::Handler::SectionCueHandler));

	SECTION("Verify Events can be created.") {
		int time = 1000;
		uint8_t* cue = section_handler->set_animation(0, 0, AnimationType::Solid);
		Event event = Event(time, cue);

		REQUIRE(event.get_time() == time);

		for (int index = 0; index < controller->get_cue_size(cue); index++) {
			REQUIRE(cue[index] == event.get_cue()[index]);
		}
	}
}
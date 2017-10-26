#ifndef SHOWCONTROLLER_H
#define SHOWCONTROLLER_H

#include "controller/maestrocontroller.h"
#include "core/maestro.h"
#include "cue/event.h"
#include "cue/show.h"
#include <vector>

using namespace PixelMaestro;

class ShowController {
	public:
		ShowController(MaestroController* maestro_controller);
		Event* add_event(uint16_t time, uint8_t *cue);
		std::vector<Event> get_events();
		uint8_t get_num_events();
		void initialize_events();
		void remove_event(uint16_t index);

	private:
		MaestroController* maestro_controller_;
		std::vector<Event> events_;
		Show* show_;

};

#endif // SHOWCONTROLLER_H

#ifndef SHOWCONTROLLER_H
#define SHOWCONTROLLER_H

#include "controller/maestrocontroller.h"
#include "core/maestro.h"
#include "cue/event.h"
#include "cue/show.h"
#include <QString>
#include <vector>

using namespace PixelMaestro;

class MaestroController;

class ShowController {
	public:
		ShowController(MaestroController* maestro_controller);
		Event* add_event(uint16_t time, uint8_t *cue);
		Event* get_event(uint16_t index);
		QString get_event_description(uint16_t index);
		std::vector<Event> get_events();
		uint8_t get_num_events();
		void initialize_events();
		void remove_event(uint16_t index);

	private:
		CueInterpreter cue_interpreter_;
		MaestroController* maestro_controller_;
		std::vector<QString> event_descriptions_;
		std::vector<Event> events_;
		Show* show_;

};

#endif // SHOWCONTROLLER_H

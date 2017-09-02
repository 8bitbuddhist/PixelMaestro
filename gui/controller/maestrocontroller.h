/*
 * MaestroController - Wrapper class for managing a Maestro using a DrawingArea.
 */

#ifndef MAESTROCONTROLLER_H
#define MAESTROCONTROLLER_H

#include "maestro.h"
#include "section.h"
#include "sectioncontroller.h"
#include "show.h"
#include "show/event.h"
#include <vector>

using namespace PixelMaestro;

class MaestroController {
	public:
		MaestroController();
		~MaestroController();
		void add_section_controller(Point* layout);
		void add_show(Event **events, unsigned char num_events, Show::TimingModes timing, bool loop);
		void delete_section_controller(int index);
		Maestro* get_maestro();
		int get_num_section_controllers();
		SectionController *get_section_controller(int index);
		Show *get_show();

	private:
		/// Maestro controlled by this controller.
		Maestro maestro_;
		/// Sections belonging to the Maestro (points to section_controllers_[index].section_). These are deleted automatically when their respective SectionController gets deleted.
		std::vector<Section*> sections_;
		/// SectionControllers that this MaestroController handles.
		std::vector<SectionController*> section_controllers_;
		Show *show_ = nullptr;

		void reassign_sections();
};

#endif // MAESTROCONTROLLER_H

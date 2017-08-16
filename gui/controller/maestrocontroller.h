/*
 * MaestroController - Wrapper class for managing a Maestro using a DrawingArea.
 */

#ifndef MAESTROCONTROLLER_H
#define MAESTROCONTROLLER_H

#include "Maestro.h"
#include "Section.h"
#include "sectioncontroller.h"
#include "Show.h"
#include "show/Event.h"
#include <vector>

using namespace PixelMaestro;

class MaestroController {
	public:
		void addSectionController();
		void addShow(Event **events, unsigned char numEvents, Show::TimingModes timing, bool loop);
		void deleteSectionController(int index);
		Maestro *getMaestro();
		int getNumSectionControllers();
		SectionController *getSectionController(int index);
		Show *getShow();

	private:
		/// Maestro controlled by this controller.
		Maestro maestro_;
		/// Sections belonging to the Maestro (points to section_controllers_[index].section_).
		std::vector<Section*> sections_;
		/// SectionControllers that this MaestroController handles.
		std::vector<SectionController> section_controllers_;
		Show show_;

		void reassignSections();
};

#endif // MAESTROCONTROLLER_H

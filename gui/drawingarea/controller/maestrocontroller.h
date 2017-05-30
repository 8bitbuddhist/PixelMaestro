#ifndef MAESTROCONTROLLER_H
#define MAESTROCONTROLLER_H

#include "Maestro.h"
#include "Section.h"
#include "sectioncontroller.h"
#include <vector>

using namespace PixelMaestro;

class MaestroController {
	public:
		MaestroController();
		void addSectionController();
		void deleteSectionController(int index);
		Maestro *getMaestro();
		int getNumSectionControllers();
		SectionController *getSectionController(int index);

	private:
		Maestro maestro_;
		std::vector<Section*> sections_;
		std::vector<SectionController> section_controllers_;

		void reassignSections();
};

#endif // MAESTROCONTROLLER_H

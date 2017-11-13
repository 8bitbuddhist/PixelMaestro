/*
 * MaestroController - Wrapper class for managing a Maestro using a DrawingArea.
 */

#ifndef MAESTROCONTROLLER_H
#define MAESTROCONTROLLER_H

#include "core/maestro.h"
#include "core/section.h"
#include <memory>
#include <vector>

using namespace PixelMaestro;

class MaestroController {
	public:
		MaestroController();
		~MaestroController();
		Section* add_section(Point dimensions);
		Maestro* get_maestro();
		Show *get_show();
		void reset_sections();

	private:
		/// Maestro controlled by this controller.
		std::shared_ptr<Maestro> maestro_;

		/// Sections belonging to the Maestro. These are deleted automatically when the MaestroController is deleted.
		std::vector<Section*> sections_;
};

#endif // MAESTROCONTROLLER_H

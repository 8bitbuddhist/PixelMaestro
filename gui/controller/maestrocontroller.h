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
		Maestro* get_maestro();
		Show *get_show();
		void reset_sections();
		Section* set_sections(uint8_t num_sections, Point dimensions = Point(10, 10));

	private:
		/// Maestro controlled by this controller.
		std::shared_ptr<Maestro> maestro_;

		/// The number of Sections in the Maestro.
		uint8_t num_sections_;

		/// Sections belonging to the Maestro.
		Section* sections_ = nullptr;
};

#endif // MAESTROCONTROLLER_H

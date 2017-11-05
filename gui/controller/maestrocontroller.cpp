#include "core/maestro.h"
#include "cue/show.h"
#include "maestrocontroller.h"
#include <memory>

using namespace PixelMaestro;

/**
 * Empty constructor.
 */
MaestroController::MaestroController() {
	maestro_ = std::unique_ptr<Maestro>(new Maestro(nullptr, 0));
}

/**
 * Adds a new Section to the Maestro.
 * @param dimensions New Section's layout.
 * @return New Section.
 */
Section* MaestroController::add_section(Point dimensions) {
	//sections_.push_back(new Section(*dimensions));
	Section* section = new Section(dimensions);
	sections_.push_back(section);
	maestro_->set_sections(sections_[0], sections_.size());
	return section;
}

/**
 * Returns the Maestro handled by this MaestroController.
 * @return Underlying Maestro.
 */
Maestro* MaestroController::get_maestro() {
	return maestro_.get();
}

/**
 * Returns the Show managed in this Maestro (if applicable)
 * @return Show managed by this Maestro.
 */
Show *MaestroController::get_show() {
	return maestro_->get_show();
}

MaestroController::~MaestroController() {
	for (Section* section : sections_) {
		delete section;
	}

	sections_.clear();
}

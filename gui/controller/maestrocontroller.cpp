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
	sections_.push_back(new Section(dimensions));
	maestro_->set_sections(*sections_.data(), sections_.size());
	return sections_[sections_.size() - 1];
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

/**
 * Removes the Section at the specified index.
 * @param section Index of the Section to be removed.
 */
void MaestroController::remove_section(uint8_t section) {
	sections_.erase(sections_.begin() + section);
	maestro_->set_sections(sections_[0], sections_.size());
}

/**
 * Re-initializes the Section array.
 */
void MaestroController::reset_sections() {
	for (uint8_t section = 0; section < sections_.size(); section++) {
		delete sections_[section];
	}

	sections_.clear();
	maestro_->set_sections(nullptr, 0);
}

MaestroController::~MaestroController() {
	for (Section* section : sections_) {
		delete section;
	}

	sections_.clear();
}

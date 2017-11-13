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
 * Re-initializes the Section array.
 */
void MaestroController::reset_sections() {
	delete [] sections_;
	set_sections(num_sections_);
}

/**
 * Initializes the Maestro's Sections.
 * @param num_sections Number of Sections to apply.
 * @param dimensions The size of each Section.
 * @return List of new Sections.
 */
Section* MaestroController::set_sections(uint8_t num_sections, Point dimensions) {
	this->sections_ = new Section[num_sections];
	this->num_sections_ = num_sections;

	// Sets the size of each Section
	for (uint8_t section = 0; section < num_sections; section++) {
		sections_[section].set_dimensions(dimensions.x, dimensions.y);
	}

	maestro_->set_sections(sections_, num_sections_);

	return this->sections_;
}

MaestroController::~MaestroController() {
	delete [] sections_;
}

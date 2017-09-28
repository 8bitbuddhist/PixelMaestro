#include "core/maestro.h"
#include "cue/show.h"
#include "maestrocontroller.h"
#include <memory>
#include "sectioncontroller.h"

using namespace PixelMaestro;

/**
 * Empty constructor.
 */
MaestroController::MaestroController() {
	maestro_ = std::unique_ptr<Maestro>(new Maestro(nullptr, 0));
	// Set framerate to 25fps
	maestro_->set_refresh_interval(40);
}

/**
 * Adds a new Section to the Maestro.
 */
std::shared_ptr<SectionController> MaestroController::add_section_controller(Point* layout) {
	std::shared_ptr<SectionController> controller = std::shared_ptr<SectionController>(new SectionController(layout));
	section_controllers_.push_back(controller);
	reassign_sections();
	return controller;
}

/**
 * Returns the Maestro handled by this MaestroController.
 * @return Underlying Maestro.
 */
Maestro* MaestroController::get_maestro() {
	return maestro_.get();
}

/**
 * Returns the number of Sections handled by this Maestro.
 * @return Number of Sections.
 */
unsigned char MaestroController::get_num_section_controllers() {
	return section_controllers_.size();
}

/**
 * Returns the SectionController at the specified index.
 * @param index Index of the desired SectionController.
 * @return SectionController at the specified index.
 */
SectionController *MaestroController::get_section_controller(unsigned char index) {
	return section_controllers_[index].get();
}

/**
 * Returns the Show managed in this Maestro (if applicable)
 * @return Show managed by this Maestro.
 */
Show *MaestroController::get_show() {
	return maestro_->get_show();
}

/**
 * Re-sets the Maestro's Sections based on the number of SectionControllers.
 */
void MaestroController::reassign_sections() {
	// Re-build the Sections vector
	this->sections_.clear();
	for (unsigned char i = 0; i < section_controllers_.size(); i++) {
		sections_.push_back(section_controllers_[i]->get_section());
	}

	maestro_->set_sections(sections_[0], sections_.size());
}

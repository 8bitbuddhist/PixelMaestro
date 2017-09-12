#include "core/maestro.h"
#include "maestrocontroller.h"
#include <memory>
#include "sectioncontroller.h"
#include "show/show.h"

using namespace PixelMaestro;

/**
 * Empty constructor.
 */
MaestroController::MaestroController() {
	maestro_ = new Maestro(nullptr, 0);
}

/**
 * Adds a new Section to the Maestro.
 */
void MaestroController::add_section_controller(Point* layout) {
	this->section_controllers_.push_back(new SectionController(layout));
	reassign_sections();
}

void MaestroController::add_show(Event** events, unsigned char num_events, Show::TimingModes timing, bool loop) {
	show_ = new Show(maestro_, events, num_events);

	show_->set_timing(timing);
	if (loop) {
		show_->set_looping(true);
	}
}

/**
 * Removes a Section from the Maestro.
 * @param index The index of the Section to remove.
 */
void MaestroController::delete_section_controller(int index) {
	// Delete the SectionController
	delete section_controllers_[index];

	// Remove the reference from the SectionController array
	section_controllers_.erase(section_controllers_.begin() + index);

	reassign_sections();
}

/**
 * Returns the Maestro handled by this MaestroController.
 * @return Underlying Maestro.
 */
Maestro* MaestroController::get_maestro() {
	return maestro_;
}

/**
 * Returns the number of Sections handled by this Maestro.
 * @return Number of Sections.
 */
int MaestroController::get_num_section_controllers() {
	return section_controllers_.size();
}

/**
 * Returns the SectionController at the specified index.
 * @param index Index of the desired SectionController.
 * @return SectionController at the specified index.
 */
SectionController *MaestroController::get_section_controller(int index) {
	return section_controllers_[index];
}

/**
 * Returns the Show managed in this Maestro (if applicable)
 * @return Show managed by this Maestro.
 */
Show *MaestroController::get_show() {
	return show_;
}

/**
 * Re-sets the Maestro's Sections based on the number of SectionControllers.
 */
void MaestroController::reassign_sections() {
	// Re-build the Sections vector
	this->sections_.clear();
	for (unsigned int i = 0; i < section_controllers_.size(); i++) {
		sections_.push_back(section_controllers_[i]->get_section().get());
	}

	maestro_->set_sections(sections_[0], sections_.size());
}

MaestroController::~MaestroController() {
	// Delete SectionControllers
	for (unsigned int i = 0; i < section_controllers_.size(); i++) {
		delete section_controllers_[i];
	}

	delete show_;
}

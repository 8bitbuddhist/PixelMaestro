#include "core/maestro.h"
#include "maestrocontroller.h"
#include <memory>
#include "sectioncontroller.h"
#include "show/show.h"

using namespace PixelMaestro;

/**
 * Empty constructor.
 */
MaestroController::MaestroController() { }

/**
 * Adds a new Section to the Maestro.
 */
void MaestroController::add_section_controller(Point* layout) {
	this->section_controllers_.push_back(new SectionController(layout));
	reassign_sections();
}

void MaestroController::add_show(Event** events, unsigned char num_events, Show::TimingModes timing, bool loop) {
	this->show_ = new Show(&this->maestro_);

	this->show_->set_timing(timing);
	this->show_->set_events(events, num_events);
	if (loop) {
		this->show_->toggle_looping();
	}
}

/**
 * Removes a Section from the Maestro.
 * @param index The index of the Section to remove.
 */
void MaestroController::delete_section_controller(int index) {
	// Delete the SectionController
	delete this->section_controllers_[index];

	// Remove the reference from the SectionController array
	this->section_controllers_.erase(this->section_controllers_.begin() + index);

	reassign_sections();
}

/**
 * Returns the Maestro handled by this MaestroController.
 * @return Underlying Maestro.
 */
Maestro* MaestroController::get_maestro() {
	return &this->maestro_;
}

/**
 * Returns the number of Sections handled by this Maestro.
 * @return Number of Sections.
 */
int MaestroController::get_num_section_controllers() {
	return this->section_controllers_.size();
}

/**
 * Returns the SectionController at the specified index.
 * @param index Index of the desired SectionController.
 * @return SectionController at the specified index.
 */
SectionController *MaestroController::get_section_controller(int index) {
	return this->section_controllers_[index];
}

/**
 * Returns the Show managed in this Maestro (if applicable)
 * @return Show managed by this Maestro.
 */
Show *MaestroController::get_show() {
	return this->show_;
}

/**
 * Re-sets the Maestro's Sections based on the number of SectionControllers.
 */
void MaestroController::reassign_sections() {
	// Re-build the Sections vector
	this->sections_.clear();
	for (unsigned int i = 0; i < this->section_controllers_.size(); i++) {
		this->sections_.push_back(this->section_controllers_[i]->get_section().get());
	}

	this->maestro_.set_sections(this->sections_[0], this->sections_.size());
}

MaestroController::~MaestroController() {
	// Delete SectionControllers
	for (unsigned int i = 0; i < this->section_controllers_.size(); i++) {
		delete this->section_controllers_[i];
	}

	delete this->show_;
}

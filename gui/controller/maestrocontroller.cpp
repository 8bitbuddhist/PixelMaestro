#include "maestro.h"
#include "maestrocontroller.h"
#include <memory>
#include "sectioncontroller.h"
#include "show.h"

using namespace PixelMaestro;

/**
 * Adds a new Section to the Maestro.
 */
void MaestroController::addSectionController(Point *layout) {
	this->section_controllers_.push_back(new SectionController(layout));
	reassignSections();
}

void MaestroController::addShow(Event **events, unsigned char numEvents, Show::TimingModes timing, bool loop) {
	this->show_ = new Show(&this->maestro_);

	this->show_->setTiming(timing);
	this->show_->setEvents(events, numEvents);
	if (loop) {
		this->show_->toggleLooping();
	}
}

/**
 * Removes a Section from the Maestro.
 * @param index The index of the Section to remove.
 */
void MaestroController::deleteSectionController(int index) {
	// Delete the SectionController
	delete this->section_controllers_[index];

	// Remove the reference from the SectionController array
	this->section_controllers_.erase(this->section_controllers_.begin() + index);

	reassignSections();
}

/**
 * Returns the Maestro handled by this MaestroController.
 * @return Underlying Maestro.
 */
Maestro *MaestroController::getMaestro() {
	return &this->maestro_;
}

/**
 * Returns the number of Sections handled by this Maestro.
 * @return Number of Sections.
 */
int MaestroController::getNumSectionControllers() {
	return this->section_controllers_.size();
}

/**
 * Returns the SectionController at the specified index.
 * @param index Index of the desired SectionController.
 * @return SectionController at the specified index.
 */
SectionController *MaestroController::getSectionController(int index) {
	return this->section_controllers_[index];
}

/**
 * Returns the Show managed in this Maestro (if applicable)
 * @return Show managed by this Maestro.
 */
Show *MaestroController::getShow() {
	return this->show_;
}

/**
 * Re-sets the Maestro's Sections based on the number of SectionControllers.
 */
void MaestroController::reassignSections() {
	// Re-build the Sections vector
	this->sections_.clear();
	for (unsigned int i = 0; i < this->section_controllers_.size(); i++) {
		this->sections_.push_back(this->section_controllers_[i]->getSection().get());
	}

	this->maestro_.setSections(this->sections_[0], this->sections_.size());
}

MaestroController::~MaestroController() {
	// Delete SectionControllers
	for (unsigned int i = 0; i < this->section_controllers_.size(); i++) {
		delete this->section_controllers_[i];
	}

	delete this->show_;
}

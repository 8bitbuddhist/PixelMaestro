#include "Maestro.h"
#include "maestrocontroller.h"
#include "sectioncontroller.h"
#include "Show.h"

using namespace PixelMaestro;

/**
 * Adds a new Section to the Maestro.
 */
void MaestroController::addSectionController() {
	this->section_controllers_.push_back(SectionController());
	this->sections_.push_back(this->section_controllers_[this->section_controllers_.size() - 1].getSection());
	reassignSections();
}

void MaestroController::addShow(Event **events, unsigned char numEvents, Show::TimingModes timing, bool loop) {
	this->show_.setTiming(timing);
	this->show_.setEvents(events, numEvents);
	if (loop) {
		this->show_.toggleLooping();
	}
	this->show_.setMaestro(&this->maestro_);
}

/**
 * Removes a Section from the Maestro.
 * @param index The index of the Section to remove.
 */
void MaestroController::deleteSectionController(int index) {
	delete &this->sections_[index];
	delete &this->section_controllers_[index];
	this->sections_.erase(this->sections_.begin() + index);
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
	return &this->section_controllers_[index];
}

/**
 * Returns the Show managed in this Maestro (if applicable)
 * @return Show managed by this Maestro.
 */
Show *MaestroController::getShow() {
	if (this->show_.getMaestro() != nullptr) {
		return &this->show_;
	}
	else {
		return nullptr;
	}
}

/**
 * Re-sets the Maestro's Sections based on the number of SectionControllers.
 */
void MaestroController::reassignSections() {
	this->maestro_.setSections(this->sections_[0], this->sections_.size());
}

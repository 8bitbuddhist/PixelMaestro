#include "Maestro.h"
#include "maestrocontroller.h"
#include "sectioncontroller.h"

using namespace PixelMaestro;

MaestroController::MaestroController() {
}

void MaestroController::addSectionController() {
	this->section_controllers_.push_back(SectionController());
	this->sections_.push_back(this->section_controllers_[this->section_controllers_.size() - 1].getSection());
	reassignSections();
}

void MaestroController::deleteSectionController(int index) {
	delete &this->sections_[index];
	delete &this->section_controllers_[index];
	this->sections_.erase(this->sections_.begin() + index);
	this->section_controllers_.erase(this->section_controllers_.begin() + index);
	reassignSections();
}

Maestro *MaestroController::getMaestro() {
	return &this->maestro_;
}

int MaestroController::getNumSectionControllers() {
	return this->section_controllers_.size();
}

SectionController *MaestroController::getSectionController(int index) {
	return &this->section_controllers_[index];
}

void MaestroController::reassignSections() {
	this->maestro_.setSections(this->sections_[0], this->sections_.size());
}

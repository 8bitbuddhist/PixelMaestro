#include "Colors.h"
#include "Pixel.h"
#include "Section.h"
#include "sectioncontroller.h"

using namespace PixelMaestro;

SectionController::SectionController(Section *section) {
	// TODO: Allow setting rows and columns
	unsigned short rows = 10;
	unsigned short columns = 10;
	this->pixels_.resize(rows * columns);
	this->section_ = section;
	this->section_->setPixels(&this->pixels_[0], rows, columns);
}

SectionController *SectionController::getOverlayController() {
	return this->overlay_controller_;
}

Section *SectionController::getSection() {
	return this->section_;
}

void SectionController::setControllerColors(Colors::RGB *colors, unsigned short numColors) {
	colors_.resize(numColors);

	for (int i = 0; i < numColors; i++) {
		colors_[i] = colors[i];
	}

	this->section_->setColors(&this->colors_[0], numColors);
}

void SectionController::setOverlayController(SectionController *overlayController, Colors::MixMode mixMode, float alpha) {
	this->overlay_controller_ = overlayController;
	this->section_->setOverlay(this->overlay_controller_->getSection(), mixMode, alpha);
}

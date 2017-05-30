#include "Colors.h"
#include "Pixel.h"
#include "Section.h"
#include "sectioncontroller.h"

using namespace PixelMaestro;

SectionController::SectionController() {
	// TODO: Allow customizing rows and columns
	unsigned short rows = 10;
	unsigned short columns = 10;
	this->pixels_.resize(rows * columns);
	this->sections_.push_back(Section());
	this->sections_[0].setPixels(&this->pixels_[0], rows, columns);
}

void SectionController::addOverlay(Colors::MixMode mixMode, float alpha) {
	this->sections_.push_back(Section());
	this->sections_[0].setOverlay(&this->sections_[1], mixMode, alpha);
}

Colors::RGB *SectionController::getColors() {
	return &this->colors_[0];
}

unsigned short SectionController::getNumColors() {
	return this->colors_.size();
}

Section *SectionController::getOverlay() {
	if (this->sections_.size() > 1) {
		return &this->sections_[1];
	}
	else {
		return nullptr;
	}
}

Section *SectionController::getSection() {
	return &this->sections_[0];
}

void SectionController::setControllerColors(Colors::RGB *colors, unsigned short numColors) {
	colors_.resize(numColors);

	// Copy provided colors to controller
	for (int i = 0; i < numColors; i++) {
		colors_[i].r = colors[i].r;
		colors_[i].g = colors[i].g;
		colors_[i].b = colors[i].b;
	}

	this->sections_[0].setColors(&this->colors_[0], numColors);
}

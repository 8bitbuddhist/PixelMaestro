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

	for (int i = 0; i < numColors; i++) {
		colors_[i] = colors[i];
	}

	this->sections_[0].setColors(&this->colors_[0], numColors);
}

void SectionController::setOverlay(Colors::MixMode mixMode, float alpha) {
	this->sections_.push_back(Section());
	this->sections_[0].setOverlay(&this->sections_[1], mixMode, alpha);
}

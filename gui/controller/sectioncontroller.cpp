#include "Colors.h"
#include "Pixel.h"
#include "Section.h"
#include "sectioncontroller.h"

using namespace PixelMaestro;

/**
 * Constructor.
 * Creates a new Section, initializes its Pixels, and assigns the Pixels to the Section.
 */
SectionController::SectionController() {
	this->pixels_.resize(layout_->getSize());
	this->section_ = new Section(&this->pixels_[0], layout_);
}

/**
 * Adds an Overlay to the Section.
 * @param mixMode The blending mode of the Overlay.
 * @param alpha The transparency of the Overlay.
 */
void SectionController::addOverlay(Colors::MixMode mixMode, float alpha) {
	// Resize Pixel grid
	int pixels = this->pixels_.size();
	this->pixels_.resize(pixels * 2);

	// Create overlay and assign Pixels
	this->section_->setOverlay(new Section::Overlay(new Section(&this->pixels_[pixels], this->layout_), mixMode, alpha));
}

/**
 * Returns the colors used in the Section.
 * @return Sections's Colors::RGB array.
 */
Colors::RGB *SectionController::getColors() {
	return &this->colors_[0];
}

/**
 * Returns the Section's Layout.
 * @return Section's Layout.
 */
Section::Layout SectionController::getLayout() {
	return *this->layout_;
}

/**
 * Returns the number of Colors in the Section.
 * @return Number of colors.
 */
unsigned short SectionController::getNumColors() {
	return this->colors_.size();
}

/**
 * Returns the Section's Overlay, if one exists.
 * @return Overlay (if it exists).
 */
Section::Overlay *SectionController::getOverlay() {
	return this->section_->getOverlay();
}

/**
 * Returns the SectionController's underlying Section.
 * @return Section controlled by the SectionController.
 */
Section *SectionController::getSection() {
	return this->section_;
}

/**
 * Copies an array of Colors into the SectionController's color array.
 * @param colors Colors to store in the SectionController.
 * @param numColors Number of colors in the array.
 */
void SectionController::setControllerColors(Colors::RGB *colors, unsigned short numColors) {
	colors_.resize(numColors);

	// Copy provided colors to controller
	for (int i = 0; i < numColors; i++) {
		colors_[i].r = colors[i].r;
		colors_[i].g = colors[i].g;
		colors_[i].b = colors[i].b;
	}

	this->section_->setColors(&this->colors_[0], numColors);
}

/**
 * Initializes the Section's Layout.
 * @param rows Number of rows in the Layout.
 * @param columns Number of columns in the Layout.
 */
void SectionController::setLayout(unsigned short rows, unsigned short columns) {
	this->layout_->rows = rows;
	this->layout_->columns = columns;
	this->pixels_.resize(layout_->getSize());
	this->section_->setPixels(&this->pixels_[0], layout_);
}

void SectionController::unsetOverlay() {
	delete this->section_->getOverlay();
}

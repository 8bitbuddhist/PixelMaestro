#include "colors.h"
#include <memory>
#include "pixel.h"
#include "section.h"
#include "sectioncontroller.h"

using namespace PixelMaestro;

/**
 * Constructor.
 * Creates a new Section, initializes its Pixels, and assigns the Pixels to the Section.
 */
SectionController::SectionController(Point *layout) {
	this->dimensions_ = layout;
	this->pixels_.resize(this->dimensions_->x * this->dimensions_->y);
	this->section_ = std::shared_ptr<Section>(new Section(&this->pixels_[0], dimensions_));

	// Initialize colors
	this->setControllerColors(Colors::COLORWHEEL, 12);
}

SectionController::SectionController(Point *layout, Colors::MixMode mixMode, float alpha) : SectionController(layout){
	this->is_overlay_ = true;
	this->mix_mode_ = mixMode;
	this->alpha_ = alpha;
}

/**
 * Adds an Overlay to the Section.
 * @param mixMode The blending mode of the Overlay.
 * @param alpha The transparency of the Overlay.
 */
void SectionController::addOverlay(Colors::MixMode mixMode, float alpha) {
	this->overlay_controller_ = std::shared_ptr<SectionController>(new SectionController(this->dimensions_, mixMode, alpha));
	this->section_->setOverlay(new Section::Overlay(this->overlay_controller_->getSection().get(), mixMode, alpha));
}

/**
 * Returns the colors used in the Section.
 * @return Sections's Colors::RGB array.
 */
Colors::RGB *SectionController::getColors() {
	return &this->colors_[0];
}

/**
 * Returns the Section's dimensions.
 * @return Section's layout.
 */
Point SectionController::getDimensions() {
	return *this->dimensions_;
}

/**
 * Returns the number of Colors in the Section.
 * @return Number of colors.
 */
unsigned short SectionController::getNumColors() {
	return this->colors_.size();
}

/**
 * Returns the Section's Overlay directly.
 * @return Section's Overlay.
 */
Section::Overlay *SectionController::getOverlay() {
	return this->section_->getOverlay();
}

/**
 * Returns the Section's Overlay, if one exists.
 * @return Overlay (if it exists).
 */
std::shared_ptr<SectionController> SectionController::getOverlayController() {
	return this->overlay_controller_;
}

/**
 * Returns the SectionController's underlying Section.
 * @return Section controlled by the SectionController.
 */
std::shared_ptr<Section> SectionController::getSection() {
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
 * Initializes the Section's dimensions.
 * @param x Size of the x-axis.
 * @param y Size of the y-axis.
 */
void SectionController::setDimensions(unsigned short x, unsigned short y) {
	this->dimensions_->x = x;
	this->dimensions_->y = y;
	this->pixels_.resize(dimensions_->x * dimensions_->y);
	this->section_->setPixels(&this->pixels_[0], dimensions_);
}

void SectionController::unsetOverlay() {
	this->overlay_controller_.reset();
}

SectionController::~SectionController() {
	if (!this->is_overlay_ && this->overlay_controller_) {
		this->unsetOverlay();
	}
}

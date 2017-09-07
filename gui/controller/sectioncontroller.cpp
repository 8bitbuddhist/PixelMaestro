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
SectionController::SectionController(Point* layout) {
	this->dimensions_ = layout;
	this->pixels_.resize(this->dimensions_->x * this->dimensions_->y);
	this->section_ = std::shared_ptr<Section>(new Section(&this->pixels_[0], dimensions_));
}

SectionController::SectionController(Point* layout, Colors::MixMode mix_mode, float alpha) : SectionController(layout){
	this->is_overlay_ = true;
	this->mix_mode_ = mix_mode;
	this->alpha_ = alpha;
}

/**
 * Adds an Overlay to the Section.
 * @param mix_mode The blending mode of the Overlay.
 * @param alpha The transparency of the Overlay.
 */
void SectionController::add_overlay(Colors::MixMode mix_mode, float alpha) {
	this->overlay_controller_ = std::shared_ptr<SectionController>(new SectionController(this->dimensions_, mix_mode, alpha));
	this->section_->set_overlay(new Section::Overlay(this->overlay_controller_->get_section().get(), mix_mode, alpha));
}

/**
 * Returns the colors used in the Section.
 * @return Sections's Colors::RGB array.
 */
Colors::RGB* SectionController::get_colors() {
	return &this->colors_[0];
}

/**
 * Returns the Section's dimensions.
 * @return Section's layout.
 */
Point SectionController::get_dimensions() {
	return *this->dimensions_;
}

/**
 * Returns the number of Colors in the Section.
 * @return Number of colors.
 */
unsigned short SectionController::get_num_colors() {
	return this->colors_.size();
}

/**
 * Returns the Section's Overlay directly.
 * @return Section's Overlay.
 */
Section::Overlay* SectionController::get_overlay() {
	return this->section_->get_overlay();
}

/**
 * Returns the Section's Overlay, if one exists.
 * @return Overlay (if it exists).
 */
std::shared_ptr<SectionController> SectionController::get_overlay_controller() {
	return this->overlay_controller_;
}

/**
 * Returns the SectionController's underlying Section.
 * @return Section controlled by the SectionController.
 */
std::shared_ptr<Section> SectionController::get_section() {
	return this->section_;
}

/**
 * Copies an array of Colors into the SectionController's color array.
 * @param colors Colors to store in the SectionController.
 * @param num_colors Number of colors in the array.
 */
void SectionController::set_colors(Colors::RGB* colors, unsigned short num_colors) {
	colors_.resize(num_colors);

	// Copy provided colors to controller
	for (int i = 0; i < num_colors; i++) {
		colors_[i].r = colors[i].r;
		colors_[i].g = colors[i].g;
		colors_[i].b = colors[i].b;
	}

	section_->get_color_animation()->set_colors(&this->colors_[0], num_colors);
}

/**
 * Initializes the Section's dimensions.
 * @param x Size of the x-axis.
 * @param y Size of the y-axis.
 */
void SectionController::set_dimensions(unsigned short x, unsigned short y) {
	this->dimensions_->x = x;
	this->dimensions_->y = y;
	this->pixels_.resize(dimensions_->x * dimensions_->y);
	this->section_->set_pixels(&this->pixels_[0], dimensions_);
}

void SectionController::unset_overlay() {
	this->overlay_controller_.reset();
}

SectionController::~SectionController() {
	if (!this->is_overlay_ && this->overlay_controller_) {
		this->unset_overlay();
	}
}

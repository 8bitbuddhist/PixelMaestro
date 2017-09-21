#include "core/colors.h"
#include "core/pixel.h"
#include "core/section.h"
#include <memory>
#include "sectioncontroller.h"

using namespace PixelMaestro;

/**
 * Constructor.
 * @param layout The dimensions of the Section.
 */
SectionController::SectionController(Point* layout) {
	this->dimensions_ = *layout;
	this->section_ = new Section(dimensions_);
}

SectionController::SectionController(Section* section, bool is_overlay) {
	this->dimensions_ = *section->get_dimensions();
	this->section_ = section;
	this->is_overlay_ = is_overlay;
}

/**
 * Adds an Overlay to the Section.
 * @param mix_mode The blending mode of the Overlay.
 * @param alpha The transparency of the Overlay.
 */
SectionController* SectionController::add_overlay(Colors::MixMode mix_mode, float alpha) {
	section_->add_overlay(mix_mode, alpha);
	overlay_controller_ = new SectionController(section_->get_overlay()->section, true);
	return overlay_controller_;
}

/**
 * Returns the controller's color palette.
 * @return Color palette.
 */
Colors::RGB* SectionController::get_colors() {
	return &this->colors_[0];
}

/**
 * Returns the number of colors in the controller.
 * @return Number of colors.
 */
unsigned char SectionController::get_num_colors() {
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
 * Returns the Section's Overlay controller.
 * @return Overlay controller.
 */
SectionController* SectionController::get_overlay_controller() {
	return this->overlay_controller_;
}

/**
 * Returns the SectionController's underlying Section.
 * @return Section controlled by the SectionController.
 */
Section* SectionController::get_section() {
	return this->section_;
}

/**
 * Copies an array of Colors into the SectionController's color array.
 * @param colors Colors to store in the SectionController.
 * @param num_colors Number of colors in the array.
 */
void SectionController::set_colors(Colors::RGB* colors, unsigned char num_colors) {
	colors_.resize(num_colors);

	// Copy provided colors to controller
	for (int i = 0; i < num_colors; i++) {
		colors_[i].r = colors[i].r;
		colors_[i].g = colors[i].g;
		colors_[i].b = colors[i].b;
	}

	section_->get_animation()->set_colors(&this->colors_[0], num_colors);
}

SectionController::~SectionController() {
	delete overlay_controller_;

	// Sections automatically delete Overlays. Only delete this Section if it's not an Overlay.
	if (!is_overlay_) {
		delete section_;
	}
}

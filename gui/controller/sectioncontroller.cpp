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
SectionController* SectionController::set_overlay(Colors::MixMode mix_mode, float alpha) {
	section_->set_overlay(mix_mode, alpha);
	overlay_controller_ = new SectionController(section_->get_overlay()->section, true);
	return overlay_controller_;
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

SectionController::~SectionController() {
	delete overlay_controller_;

	// Sections automatically delete Overlays. Only delete this Section if it's not an Overlay.
	if (!is_overlay_) {
		delete section_;
	}
}

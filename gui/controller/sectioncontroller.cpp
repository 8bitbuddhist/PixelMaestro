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

/**
 * Overlay constructor.
 * @param section Section that this Overlay controls.
 * @param parent_controller Parent SectionController.
 */
SectionController::SectionController(Section* section, SectionController* parent_controller) {
	this->dimensions_ = *section->get_dimensions();
	this->section_ = section;
	this->parent_controller_ = parent_controller;
}

/**
 * Returns the Section's Canvas controller.
 * @return Section's Canvas controller.
 */
CanvasController* SectionController::get_canvas_controller() {
	return canvas_controller_.get();
}

/**
 * Sets the Canvas Controller.
 * @param canvas_controller New Canvas Controller.
 * @return new Canvas controller.
 */
CanvasController* SectionController::set_canvas_controller(CanvasController *canvas_controller) {
	if (canvas_controller == nullptr) {
		canvas_controller_.reset();
		return nullptr;
	}
	else {
		canvas_controller_ = std::unique_ptr<CanvasController>(canvas_controller);
		return canvas_controller_.get();
	}
}

/**
 * Adds an Overlay to the Section.
 * @param mix_mode The blending mode of the Overlay.
 * @param alpha The transparency of the Overlay.
 */
SectionController* SectionController::set_overlay(Colors::MixMode mix_mode, float alpha) {
	section_->set_overlay(mix_mode, alpha);
	overlay_controller_ = new SectionController(section_->get_overlay()->section, this);
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
 * Returns the SectionController that this Overlay belongs to.
 * @return Parent SectionController.
 */
SectionController* SectionController::get_parent_controller() {
	return parent_controller_;
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
	if (parent_controller_ != nullptr) {
		delete section_;
	}
}

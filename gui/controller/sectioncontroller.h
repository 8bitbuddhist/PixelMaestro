/*
 * SectionController - Wrapper class for managing a Section using a MaestroController.
 */

#ifndef SECTIONCONTROLLER_H
#define SECTIONCONTROLLER_H

#include "controller/palettecontroller.h"
#include "core/colors.h"
#include "core/pixel.h"
#include "core/section.h"
#include <vector>

using namespace PixelMaestro;

class SectionController {
	public:
		/// Stores the current Palette (used only by MaestroControl)
		PaletteController::Palette* palette_ = nullptr;

		SectionController(Point* layout);
		SectionController(Section* section, SectionController* parent_controller_);
		~SectionController();
		Section::Overlay* get_overlay();
		SectionController* get_overlay_controller();
		SectionController* get_parent_controller();
		Section* get_section();
		SectionController* set_overlay(Colors::MixMode mix_mode, float alpha = 0.5);

	private:
		/// Stores the size of the grid.
		Point dimensions_ = {0, 0};

		/**
		 * Controller for the Overlay Section.
		 * Avoided smart pointers due to the possibility of overlay_controller_ and section_ both trying to free the same Section at the same time.
		 */
		SectionController* overlay_controller_ = nullptr;

		/// Pointer to the parent controller (applies to Overlays only).
		SectionController* parent_controller_  = nullptr;

		/// Stores the Section.
		Section* section_ = nullptr;
};

#endif // SECTIONCONTROLLER_H

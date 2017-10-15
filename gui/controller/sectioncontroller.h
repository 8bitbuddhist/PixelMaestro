/*
 * SectionController - Wrapper class for managing a Section using a MaestroController.
 */

#ifndef SECTIONCONTROLLER_H
#define SECTIONCONTROLLER_H

#include "core/colors.h"
#include "core/pixel.h"
#include "core/section.h"
#include <vector>

using namespace PixelMaestro;

class SectionController {
	public:
		/// Determines whether this Section is an Overlay.
		bool is_overlay_ = false;

		SectionController(Point* layout);
		SectionController(Section* section, bool is_overlay = false);
		~SectionController();
		Section::Overlay* get_overlay();
		SectionController* get_overlay_controller();
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

		/// Stores the Section.
		Section* section_ = nullptr;
};

#endif // SECTIONCONTROLLER_H

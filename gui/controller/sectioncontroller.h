/*
 * SectionController - Wrapper class for managing a Section using a MaestroController.
 */

#ifndef SECTIONCONTROLLER_H
#define SECTIONCONTROLLER_H

#include "core/colors.h"
#include "core/pixel.h"
#include "core/section.h"
#include <memory>
#include <vector>

using namespace PixelMaestro;

class SectionController {
	public:
		SectionController(Point* layout);
		SectionController(Section* section, bool is_overlay = false);
		void add_overlay(Colors::MixMode mix_mode, float alpha = 0.5);
		Colors::RGB* get_colors();
		Point get_dimensions();
		unsigned char get_num_colors();
		Section::Overlay* get_overlay();
		std::shared_ptr<SectionController> get_overlay_controller();
		std::shared_ptr<Section> get_section();
		void set_colors(Colors::RGB* colors, unsigned char num_colors);
		void set_dimensions(unsigned short x, unsigned short y);
		void unset_overlay();

	private:
		/// Colors used by the Section and its Overlay.
		std::vector<Colors::RGB> colors_;

		/// Stores the size of the grid.
		Point dimensions_ = {0, 0};

		/// Determines whether this Section is an Overlay.
		bool is_overlay_ = false;

		/// Controller for the Overlay Section.
		std::shared_ptr<SectionController> overlay_controller_ = nullptr;

		/// Stores the Section.
		std::shared_ptr<Section> section_ = nullptr;
};

#endif // SECTIONCONTROLLER_H

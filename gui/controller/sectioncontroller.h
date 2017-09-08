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
		SectionController(Point* layout, Colors::MixMode mix_mode, float alpha);
		~SectionController();
		void add_overlay(Colors::MixMode mix_mode, float alpha = 0.5);
		Colors::RGB* get_colors();
		Point get_dimensions();
		unsigned short get_num_colors();
		Section::Overlay* get_overlay();
		std::shared_ptr<SectionController> get_overlay_controller();
		std::shared_ptr<Section> get_section();
		void set_colors(Colors::RGB* colors, unsigned short num_colors);
		void set_dimensions(unsigned short x, unsigned short y);
		void unset_overlay();

		bool is_overlay_ = false;

	private:
		/// The amount of blending to apply to the Overlay.
		float alpha_ = 0.0;

		/// Colors used by the Section and its Overlay.
		std::vector<Colors::RGB> colors_;

		/// Layout of the section (defaults to 10 x 10)
		Point* dimensions_ = nullptr;

		/// Overlay MixMode to use.
		Colors::MixMode mix_mode_;

		/// Controller for the Overlay Section.
		std::shared_ptr<SectionController> overlay_controller_ = nullptr;

		/// Pixels assigned to the Section and its Overlay.
		std::vector<Pixel> pixels_;

		/// Stores the Section.
		std::shared_ptr<Section> section_ = nullptr;
};

#endif // SECTIONCONTROLLER_H

/*
 * SectionController - Wrapper class for managing a Section using a MaestroController.
 */

#ifndef SECTIONCONTROLLER_H
#define SECTIONCONTROLLER_H

#include "colors.h"
#include <memory>
#include "pixel.h"
#include "section.h"
#include <vector>

using namespace PixelMaestro;

class SectionController {
	public:
		SectionController(Section::Layout *layout);
		SectionController(Section::Layout *layout, Colors::MixMode mixMode, float alpha);
		~SectionController();
		void addOverlay(Colors::MixMode mixMode, float alpha);
		Colors::RGB *getColors();
		Section::Layout getLayout();
		unsigned short getNumColors();
		Section::Overlay *getOverlay();
		std::shared_ptr<SectionController> getOverlayController();
		std::shared_ptr<Section> getSection();
		void setControllerColors(Colors::RGB *colors, unsigned short numColors);
		void setLayout(unsigned short rows, unsigned short columns);
		void unsetOverlay();

		bool is_overlay_ = false;

	private:
		/// Colors used by the Section and its Overlay.
		std::vector<Colors::RGB> colors_;

		Colors::MixMode mix_mode_;
		float alpha_ = 0.0;

		std::shared_ptr<SectionController> overlay_controller_;

		/// Pixels assigned to the Section and its Overlay.
		std::vector<Pixel> pixels_;
		/// Stores the Section.
		std::shared_ptr<Section> section_;
		/// Layout of the section (defaults to 10 x 10)
		Section::Layout *layout_;
};

#endif // SECTIONCONTROLLER_H

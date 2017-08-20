/*
 * SectionController - Wrapper class for managing a Section using a MaestroController.
 */

#ifndef SECTIONCONTROLLER_H
#define SECTIONCONTROLLER_H

#include "Colors.h"
#include <memory>
#include "Pixel.h"
#include "Section.h"
#include <vector>

using namespace PixelMaestro;

class SectionController {
	public:
		SectionController();
		~SectionController();
		void addOverlay(Colors::MixMode mixMode, float alpha);
		Colors::RGB *getColors();
		Section::Layout getLayout();
		unsigned short getNumColors();
		Section::Overlay *getOverlay();
		std::shared_ptr<Section> getSection();
		void setControllerColors(Colors::RGB *colors, unsigned short numColors);
		void setLayout(unsigned short rows, unsigned short columns);
		void unsetOverlay();

	private:
		/// Colors used by the Section and its Overlay.
		std::vector<Colors::RGB> colors_;
		/// Pixels assigned to the Section and its Overlay.
		std::vector<Pixel> pixels_;
		/// Stores the Section.
		std::shared_ptr<Section> section_;
		/// Layout of the section (defaults to 10 x 10)
		Section::Layout *layout_ = new Section::Layout(10, 10);
};

#endif // SECTIONCONTROLLER_H

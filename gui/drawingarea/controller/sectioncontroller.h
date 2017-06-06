#ifndef SECTIONCONTROLLER_H
#define SECTIONCONTROLLER_H

#include "Colors.h"
#include "Pixel.h"
#include "Section.h"
#include <vector>

using namespace PixelMaestro;

class SectionController {
	public:
		SectionController();
		// TODO: Make colors_ private
		std::vector<Colors::RGB> colors_;

		void addOverlay(Colors::MixMode mixMode, float alpha);
		Colors::RGB *getColors();
		Section::Layout getLayout();
		unsigned short getNumColors();
		Section *getOverlay();
		Section *getSection();
		void setControllerColors(Colors::RGB *colors, unsigned short numColors);
		void setLayout(unsigned short rows, unsigned short columns);

	private:
		std::vector<Pixel> pixels_;
		std::vector<Section> sections_;
		Section::Layout layout_ = {10, 10};	// Default to 10 x 10 grid
};

#endif // SECTIONCONTROLLER_H

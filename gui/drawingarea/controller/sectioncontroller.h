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
		unsigned short getNumColors();
		Section *getOverlay();
		Section *getSection();
		void setControllerColors(Colors::RGB *colors, unsigned short numColors);

	private:
		std::vector<Pixel> pixels_;
		std::vector<Section> sections_;
};

#endif // SECTIONCONTROLLER_H

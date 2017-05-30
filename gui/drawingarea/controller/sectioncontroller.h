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

		Section *getSection();
		Section *getOverlay();
		void setControllerColors(Colors::RGB *colors, unsigned short numColors);
		void setOverlay(Colors::MixMode mixMode, float alpha);

	private:
		std::vector<Pixel> pixels_;
		std::vector<Section> sections_;
};

#endif // SECTIONCONTROLLER_H

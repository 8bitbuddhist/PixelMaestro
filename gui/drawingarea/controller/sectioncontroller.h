#ifndef SECTIONCONTROLLER_H
#define SECTIONCONTROLLER_H

#include "Colors.h"
#include "Pixel.h"
#include "Section.h"
#include <vector>

using namespace PixelMaestro;

class SectionController {
	public:
		SectionController(Section *section);
		std::vector<Colors::RGB> colors_;

		Section *getSection();
		SectionController *getOverlayController();
		void setControllerColors(Colors::RGB *colors, unsigned short numColors);
		void setOverlayController(SectionController *overlayController, Colors::MixMode mixMode, float alpha);

	private:
		std::vector<Pixel> pixels_;
		Section *section_;
		SectionController *overlay_controller_;
};

#endif // SECTIONCONTROLLER_H

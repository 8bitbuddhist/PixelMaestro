/*
 * Font.h - Base class for Pattern fonts.
 */
#ifndef FONT_H
#define FONT_H

#include "../../section.h"

namespace PixelMaestro {
	class Font {
		public:
			/// The size of the font (e.g. a 5x8 font means 5 columns and 8 rows).
			Section::Layout *size = nullptr;
			virtual unsigned char *getChar(unsigned char character) = 0;
	};
}

#endif // FONT_H

/*
 * Font.h - Base class for Pattern fonts.
 */
#ifndef FONT_H
#define FONT_H

#include "../../core/point.h"

namespace PixelMaestro {
	class Font {
		public:
			/// The size of the font (e.g. a 5x8 font means 5 columns and 8 rows).
			Point size = {0, 0};
			virtual unsigned char* get_char(unsigned char character) = 0;

			virtual ~Font() {}
	};
}

#endif // FONT_H

/*
 * Font.h - Base class for Pattern fonts.
 */
#ifndef FONT_H
#define FONT_H

#include "../../point.h"

namespace PixelMaestro {
	class Font {
		public:
			~Font() {
				if (size != nullptr) {
					delete size;
				}
			}

			/// The size of the font (e.g. a 5x8 font means 5 columns and 8 rows).
			Point* size = nullptr;
			virtual unsigned char* get_char(unsigned char character) = 0;
	};
}

#endif // FONT_H

/*
 * Font.h - Base class for Pattern fonts.
 */
#ifndef FONT_H
#define FONT_H

#include <stdint.h>
#include "../../core/point.h"

namespace PixelMaestro {
	class Font {
		public:
			/// Types of fonts available.
			enum Type {
				Font5x8
			};

			/// The size of the font (e.g. a 5x8 font means 5 columns and 8 rows).
			Point size = {0, 0};
			virtual uint8_t* get_char(uint8_t character) = 0;

			virtual ~Font() {}
	};
}

#endif // FONT_H

/*
 * Palette - Stores information about a color palette.
 */

#ifndef PALETTE_H
#define PALETTE_H

#include <stdlib.h>
#include "colors.h"

namespace PixelMaestro {
	class Palette {
		public:
			Palette(Colors::RGB* colors, uint8_t size);
			Palette(const Palette& other);
			Palette& operator=(const Palette& other);
			~Palette();
			Colors::RGB* get_color_at_index(uint8_t index) const;
			Colors::RGB* get_colors() const;
			uint8_t get_num_colors() const;
			void set_colors(Colors::RGB* colors, uint8_t num_colors);

		private:
			/// The colors in the Palette.
			Colors::RGB* colors_ = nullptr;

			/// The number of colors in the Palette.
			uint8_t num_colors_ = 0;
	};
}

#endif // PALETTE_H
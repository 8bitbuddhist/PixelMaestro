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
			Palette(Colors::RGB* colors, uint8_t size, bool delete_colors_on_destruction = false);
			Palette(const Palette& other);
			Palette& operator=(const Palette& other);
			~Palette();
			Colors::RGB* get_color_at_index(uint8_t index) const;
			Colors::RGB* get_colors() const;
			bool get_delete_colors_on_destruction() const;
			uint8_t get_size() const;
			void set_colors(Colors::RGB* colors, uint8_t size);

		private:
			/// The colors in the Palette.
			Colors::RGB* colors_ = nullptr;

			/// If true, deletes the colors array when the Palette is destructed.
			bool delete_colors_on_destruction_ = false;

			/// The number of colors in the Palette.
			uint8_t size_ = 0;
	};
}

#endif // PALETTE_H
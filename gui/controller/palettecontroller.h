#ifndef PALETTECONTROLLER_H
#define PALETTECONTROLLER_H

#include "core/colors.h"
#include <string>
#include <vector>

using namespace PixelMaestro;

class PaletteController {
	public:
		struct Palette {
			const char* name;
			std::vector<Colors::RGB> palette;

			Palette(const char* new_name, Colors::RGB* colors, uint8_t num_colors) {
				this->name = new_name;
				for (uint8_t i = 0; i < num_colors; i++) {
					palette.push_back(colors[i]);
				}
			}
		};

		PaletteController();
		Palette* add_palette(const char* name, Colors::RGB* colors, uint8_t num_colors);
		Palette* get_palette(uint8_t index);
		Palette* get_palette(std::string name);
		std::vector<Palette> get_palettes();
		void remove_palette(uint8_t index);

	private:
		std::vector<Palette> palettes_;
};

#endif // PALETTECONTROLLER_H

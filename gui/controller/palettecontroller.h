#ifndef PALETTECONTROLLER_H
#define PALETTECONTROLLER_H

#include "core/colors.h"
#include <QString>
#include <string>
#include <vector>

using namespace PixelMaestro;

class PaletteController {
	public:
		struct Palette {
			QString name = "";
			std::vector<Colors::RGB> colors;

			bool operator==(Colors::RGB* section_colors) {
				bool matches = true;
				for (uint8_t i = 0; i < this->colors.size(); i++) {
					if (this->colors.at(i) != section_colors[i]) {
						matches = false;
					}
				}
				return matches;
			}

			Palette(QString new_name, Colors::RGB* colors, uint8_t num_colors) {
				this->name = new_name;
				for (uint8_t i = 0; i < num_colors; i++) {
					this->colors.push_back(colors[i]);
				}
			}
		};

		PaletteController();
		Palette* add_palette(QString name, Colors::RGB* colors, uint8_t num_colors);
		Palette* get_palette(uint8_t index);
		Palette* get_palette(QString name);
		std::vector<Palette>* get_palettes();
		void initialize_palettes();
		void remove_palette(uint8_t index);

	private:
		std::vector<Palette> palettes_;
};

#endif // PALETTECONTROLLER_H

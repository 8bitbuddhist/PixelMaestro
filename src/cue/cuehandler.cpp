/*
 * CueHandler - Base class for mapping Cues to PixelMaestro actions.
 */

#include "cuehandler.h"

namespace PixelMaestro {

	/**
	 * Extracts a Palette from a Cue.
	 * @param cue The Cue starting at the Palette's address.
	 * @param num_colors The number of colors in the Palette.
	 * @return The New Palette.
	 */
	Palette* CueHandler::deserialize_palette(uint8_t *cue, uint8_t num_colors) {
		uint16_t current_color_index = 0;
		Colors::RGB colors[num_colors];
		for (uint8_t i = 0; i < num_colors; i++) {
			colors[i].r = cue[current_color_index];
			current_color_index++;
			colors[i].g = cue[current_color_index];
			current_color_index++;
			colors[i].b = cue[current_color_index];
			current_color_index++;
		}
		return new Palette(colors, num_colors);
	}

	/**
	 * Returns the Section/Layer corresponding to the given Section ID and Layer level.
	 * @param section Index of the Section in the Maestro.
	 * @param layer Layer depth level.
	 * @return Matching Section/Layer or nullptr if not found.
	 */
	Section* CueHandler::get_section(uint8_t section_id, uint8_t layer_id) const {
		Section* section = controller_->get_maestro()->get_section(section_id);

		/*
		 * Iterate until we hit the desired Layer level.
		 * If there is no Layer at that level, create it.
		 * Important: Layers start at index 1, not 0!
		 */
		if (section != nullptr && layer_id > 0) {
			for (uint8_t i = 0; i < layer_id; i++) {
				if (section->get_layer() != nullptr) {
					section = section->get_layer()->section;
				}
				else {
					section = section->set_layer()->section;
				}
			}
		}

		return section;
	}

	/**
	 * Serializes a Palette into a Cue.
	 * @param cue The address in the Cue where the Palette will be written.
	 * @param palette The Palette to store.
	 * @return Index in the Cue immediately after the Palette.
	 */
	uint16_t CueHandler::serialize_palette(uint8_t *cue, Palette *palette) {
		uint16_t colors_index = 0;
		for (uint8_t i = 0; i < palette->get_num_colors(); i++) {
			Colors::RGB* color = palette->get_color_at_index(i);
			cue[colors_index] = color->r;
			colors_index++;
			cue[colors_index] = color->g;
			colors_index++;
			cue[colors_index] = color->b;
			colors_index++;
		}

		return colors_index;
	}
}

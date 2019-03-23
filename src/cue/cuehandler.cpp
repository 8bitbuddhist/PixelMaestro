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
	Palette* CueHandler::deserialize_palette(const uint8_t* cue, uint8_t num_colors) {
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
	uint16_t CueHandler::serialize_palette(uint8_t* cue, Palette *palette) {
		uint16_t index = 0;
		for (uint8_t i = 0; i < palette->get_num_colors(); i++) {
			Colors::RGB* color = palette->get_color_at_index(i);
			cue[index] = color->r;
			index++;
			cue[index] = color->g;
			index++;
			cue[index] = color->b;
			index++;
		}

		return index;
	}

	/**
	 * Assembles the first part of a Cue.
	 * @param handler_byte The CueHandler that the Cue belongs to.
	 * @param action_byte The action being performed.
	 * @return The current index in the Cue.
	 */
	uint8_t CueHandler::start_cue(uint8_t handler_byte, uint8_t action_byte) {
		uint8_t index = (uint8_t)CueController::Byte::PayloadByte;
		controller_->get_buffer()[index] = handler_byte;
		controller_->get_buffer()[++index] = action_byte;

		return index;
	}

	/**
	 * Assembles the first part of a Cue.
	 * @param handler_byte The CueHandler that the Cue belongs to.
	 * @param action_byte The action being performed.
	 * @param section_num The ID of the affected Section.
	 * @param layer_num The ID of the affected Layer.
	 * @return The current index in the Cue.
	 */
	uint8_t CueHandler::start_cue(uint8_t handler_byte, uint8_t action_byte, uint8_t section_num, uint8_t layer_num) {
		uint8_t index = start_cue(handler_byte, action_byte);
		controller_->get_buffer()[++index] = section_num;
		controller_->get_buffer()[++index] = layer_num;

		return index;
	}
}

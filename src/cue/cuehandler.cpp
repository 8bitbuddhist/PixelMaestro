/*
 * CueHandler - Base class for mapping Cues to PixelMaestro actions.
 */

#include "cuehandler.h"

namespace PixelMaestro {
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
}

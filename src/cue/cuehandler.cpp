/*
 * CueHandler - Base class for mapping Cues to PixelMaestro actions.
 */

#include "cuehandler.h"

namespace PixelMaestro {
	/**
	 * Returns the Section/Overlay corresponding to the given Section ID and Overlay level.
	 * @param section Index of the Section in the Maestro.
	 * @param overlay Overlay depth level.
	 * @return Matching Section/Overlay or nullptr if not found.
	 */
	Section* CueHandler::get_section(uint8_t section_id, uint8_t overlay_id) {

		if (section_id >= controller_->get_maestro()->get_num_sections()) {
			return nullptr;
		}

		Section* section = controller_->get_maestro()->get_section(section_id);

		/*
		 * Iterate until we hit the desired Overlay level.
		 * If there is no Overlay at that level, return nothing.
		 */
		if (overlay_id > 0) {
			for (uint8_t i = 0; i < overlay_id; i++) {
				if (section->get_overlay() != nullptr) {
					section = section->get_overlay()->section;
				}
				else {
					return nullptr;
				}
			}
		}

		return section;
	}
}

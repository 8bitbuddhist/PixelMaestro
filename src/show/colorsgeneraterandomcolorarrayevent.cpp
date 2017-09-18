#include "colorsgeneraterandomcolorarrayevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Generates a set of random colors.
	 * @param time Time until the Event runs.
	 * @param new_array Array to store the new colors.
	 * @param base_color Seed color used to generate other colors.
	 * @param num_colors The number of colors to generate.
	 * @param range Range of possible new values.
	 */
	ColorsGenerateRandomColorArrayEvent::ColorsGenerateRandomColorArrayEvent(unsigned long time, Colors::RGB* new_array, Colors::RGB* base_color, unsigned int num_colors, float range) : Event(time) {
		this->new_array_ = new_array;
		this->base_color_ = base_color;
		this->num_colors_ = num_colors;
		this->range_ = range;
	}

	void ColorsGenerateRandomColorArrayEvent::run() {
		Colors::generate_random_color_array(new_array_, base_color_, num_colors_, range_);
	}
}

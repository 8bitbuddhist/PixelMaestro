#include "colorsgeneraterandomcolorarrayevent.h"

namespace PixelMaestro {
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

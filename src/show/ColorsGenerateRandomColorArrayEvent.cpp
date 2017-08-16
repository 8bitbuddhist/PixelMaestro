#include "ColorsGenerateRandomColorArrayEvent.h"

namespace PixelMaestro {
	ColorsGenerateRandomColorArrayEvent::ColorsGenerateRandomColorArrayEvent(unsigned long time, Colors::RGB *newArray, Colors::RGB *baseColor, unsigned int numColors, float range) : Event(time) {
		this->new_array_ = newArray;
		this->base_color_ = baseColor;
		this->num_colors_ = numColors;
		this->range_ = range;
	}

	void ColorsGenerateRandomColorArrayEvent::run() {
		Colors::generateRandomColorArray(this->new_array_, this->base_color_, this->num_colors_, this->range_);
	}
}

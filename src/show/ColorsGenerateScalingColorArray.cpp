#include "ColorsGenerateScalingColorArray.h"

namespace PixelMaestro {
	ColorsGenerateScalingColorArray::ColorsGenerateScalingColorArray(unsigned long time, Colors::RGB newArray[], Colors::RGB *baseColor, Colors::RGB *targetColor, unsigned int numColors, bool reverse) : Transition(time) {
		this->new_array_ = newArray;
		this->base_color_ = baseColor;
		this->target_color_ = targetColor;
		this->num_colors_ = numColors;
		this->reverse_ = reverse;
	}

	ColorsGenerateScalingColorArray::ColorsGenerateScalingColorArray(unsigned long time, Colors::RGB newArray[], Colors::RGB *baseColor, unsigned int numColors, unsigned char threshold, bool reverse) : Transition(time) {
		this->new_array_ = newArray;
		this->base_color_ = baseColor;
		this->num_colors_ = numColors;
		this->threshold_ = threshold;
		this->reverse_ = reverse;
	}

	void ColorsGenerateScalingColorArray::run() {
		if (this->target_color_ != nullptr) {
			Colors::generateScalingColorArray(this->new_array_, this->base_color_, this->target_color_, this->threshold_, this->reverse_);
		}
		else {
			Colors::generateScalingColorArray(this->new_array_, this->base_color_, this->num_colors_, this->threshold_, this->reverse_);
		}
	}
}

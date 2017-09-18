#include "colorsgeneratescalingcolorarrayevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Generates an array of scaling colors from a base color to a target color.
	 * @param time Time until the Event runs.
	 * @param new_array Array to store the new colors.
	 * @param base_color Base color used to populate the array.
	 * @param target_color Color that the array scales to.
	 * @param num_colors Number of colors to generate.
	 * @param reverse If true, mirrors the array from the target color back to the base color.
	 */
	ColorsGenerateScalingColorArrayEvent::ColorsGenerateScalingColorArrayEvent(unsigned long time, Colors::RGB new_array[], Colors::RGB* base_color, Colors::RGB* target_color, unsigned int num_colors, bool reverse) : Event(time) {
		this->new_array_ = new_array;
		this->base_color_ = base_color;
		this->target_color_ = target_color;
		this->num_colors_ = num_colors;
		this->reverse_ = reverse;
	}

	/**
	 * Constructor. Generates an array of scaling colors by incrementing the base color.
	 * @param time Time until the Event runs.
	 * @param new_array Array to store the new colors.
	 * @param base_color Base color used to populate the array.
	 * @param num_colors Number of colors to generate.
	 * @param threshold Amount to increment.
	 * @param reverse If true, mirrors the array from the target color back to the base color.
	 */
	ColorsGenerateScalingColorArrayEvent::ColorsGenerateScalingColorArrayEvent(unsigned long time, Colors::RGB new_array[], Colors::RGB* base_color, unsigned int num_colors, unsigned char threshold, bool reverse) : Event(time) {
		this->new_array_ = new_array;
		this->base_color_ = base_color;
		this->num_colors_ = num_colors;
		this->threshold_ = threshold;
		this->reverse_ = reverse;
	}

	void ColorsGenerateScalingColorArrayEvent::run() {
		if (target_color_ != nullptr) {
			Colors::generate_scaling_color_array(new_array_, base_color_, target_color_, num_colors_, reverse_);
		}
		else {
			Colors::generate_scaling_color_array(new_array_, base_color_, num_colors_, threshold_, reverse_);
		}
	}
}

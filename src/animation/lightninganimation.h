#ifndef LIGHTNINGANIMATION_H
#define LIGHTNINGANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class LightningAnimation : public Animation {
		public:
			LightningAnimation(Colors::RGB* colors, uint8_t num_colors, uint8_t num_bolts = 1, uint8_t down_threshold = 90, uint8_t up_threshold = 166, uint8_t fork_chance_ = 4);
			~LightningAnimation();
			uint8_t get_bolt_count();
			uint8_t get_fork_chance();
			uint8_t get_down_threshold();
			uint8_t get_up_threshold();
			void set_bolt_count(uint8_t bolt_count);
			void set_fork_chance(uint8_t fork_chance);
			void set_thresholds(uint8_t down_threshold, uint8_t up_threshold);
			void update(Section* section);

		private:
			/// The chance that a bolt will drift downwards (or left in vertical mode).
			uint8_t down_threshold_;

			/// The chance of a bolt forking (reduces based on the number of off-shoot bolts. Defaults to 20.
			uint8_t fork_chance_;

			/// The number of bolts to display. Defaults to 1.
			uint8_t num_bolts_;

			/// The chance that a bolt will drift upwards (or right in vertical mode).
			uint8_t up_threshold_;

			void draw_bolt_horizontal(uint8_t bolt_num, Section* section, Point* start, uint8_t down_threshold, uint8_t up_threshold, uint8_t fork_chance);
			void draw_bolt_vertical(uint8_t bolt_num, Section* section, Point* start, uint8_t left_threshold, uint8_t right_threshold, uint8_t fork_chance);
	};
}

#endif // LIGHTNINGANIMATION_H

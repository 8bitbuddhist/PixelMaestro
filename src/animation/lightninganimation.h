#ifndef LIGHTNINGANIMATION_H
#define LIGHTNINGANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class LightningAnimation : public Animation {
		public:
			explicit LightningAnimation(Section* section);
			~LightningAnimation();
			uint8_t get_bolt_count() const;
			uint8_t get_fork_chance() const;
			int8_t get_drift() const;
			void set_bolt_count(uint8_t bolt_count);
			void set_drift(int8_t drift);
			void set_fork_chance(uint8_t fork_chance);
			void update();

		private:
			Colors::RGB black_ = {0, 0, 0};

			/**
			 * The rate that a bolt will drift.
			 * Negative values determine the rate of drift to the left (or down if in vertical mode).
			 * Positive values determine the rate of drift to the right (or up if in vertical mode).
			 */
			int8_t drift_ = 0;

			/// The chance of a bolt forking (reduces based on the number of off-shoot bolts. Defaults to 20.
			uint8_t fork_chance_ = 4;

			/// The number of bolts to display. Defaults to 1.
			uint8_t num_bolts_ = 1;

			void draw_bolt_horizontal(uint8_t bolt_num, Point* start, int8_t drift, uint8_t fork_chance, uint8_t max_fork_length);
			void draw_bolt_vertical(uint8_t bolt_num, Point* start, int8_t drift, uint8_t fork_chance, uint8_t max_fork_length);
	};
}

#endif // LIGHTNINGANIMATION_H

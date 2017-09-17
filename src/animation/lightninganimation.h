#ifndef LIGHTNINGANIMATION_H
#define LIGHTNINGANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class LightningAnimation : public Animation {
		public:
			LightningAnimation(unsigned char num_bolts = 1, unsigned char down_threshold = 90, unsigned char up_threshold = 166, unsigned char fork_chance_ = 4, Colors::RGB* colors = nullptr, unsigned char num_colors = 0);
			unsigned char get_bolt_count();
			unsigned char get_fork_chance();
			unsigned char get_down_threshold();
			unsigned char get_up_threshold();
			void set_bolt_count(unsigned char bolt_count);
			void set_fork_chance(unsigned char fork_chance);
			void set_thresholds(unsigned char down_threshold, unsigned char up_threshold);
			void update(Section* section);

		private:
			unsigned char down_threshold_;

			/// The chance of a bolt forking (reduces based on the number of off-shoot bolts. Defaults to 20.
			unsigned char fork_chance_;

			/// The number of bolts to display. Defaults to 1.
			unsigned char num_bolts_;

			unsigned char up_threshold_;

			void draw_bolt_horizontal(unsigned char bolt_num, Section* section, Point* start, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance);
			void draw_bolt_vertical(unsigned char bolt_num, Section* section, Point* start, unsigned char left_threshold, unsigned char right_threshold, unsigned char fork_chance);
	};
}

#endif // LIGHTNINGANIMATION_H

#ifndef LIGHTNINGANIMATION_H
#define LIGHTNINGANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class LightningAnimation : public Animation {
		public:
			LightningAnimation(unsigned char num_bolts, unsigned char down_threshold = 35, unsigned char up_threshold = 65, unsigned char fork_chance_ = 2, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update(Section* section);

		private:
			unsigned char down_threshold_;

			/// The chance of a bolt forking (reduces based on the number of off-shoot bolts. Defaults to 20.
			unsigned char fork_chance_;

			/// The number of bolts to display. Defaults to 1.
			unsigned char num_bolts_;

			unsigned char up_threshold_;

			void draw_bolt(Section* section, Point* start, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance);
	};
}

#endif // LIGHTNINGANIMATION_H

/*
 * AnimationTiming - Class for managing time-sensitive actions for Animations.
 */

#ifndef ANIMATIONTIMING_H
#define ANIMATIONTIMING_H

#include <stdint.h>
#include "animation/animation.h"
#include "timing.h"

namespace PixelMaestro {
	class Animation;
	class AnimationTiming : public Timing {
		public:
			AnimationTiming(Animation* animation);
			uint16_t get_pause();
			uint8_t get_step_count();
			void recalculate_step_count();
			void set_interval(uint16_t interval, uint16_t pause = 0);

		private:
			/// The Timing's parent Animation.
			Animation* animation_ = nullptr;

			/// The amount of time (in milliseconds) to wait before starting an animation cycle. Defaults to 0.
			uint16_t pause_;

			/// The number of steps from the current cycle to the next cycle.
			uint8_t step_count_ = 1;
	};
}

#endif // ANIMATIONTIMING_H
/*
 * AnimationTimer - Class for managing time-sensitive actions for Animations.
 */

#ifndef ANIMATIONTIMER_H
#define ANIMATIONTIMER_H

#include <stdint.h>
#include "../../animation/animation.h"
#include "timer.h"

namespace PixelMaestro {
	class Animation;
	class AnimationTimer : public Timer {
		public:
			AnimationTimer(Animation* animation);
			uint16_t get_delay() const;
			uint8_t get_step_count() const;
			void recalculate_step_count();
			void set_interval(uint16_t interval, uint16_t delay = 0);
			bool update(const uint32_t& current_time);

		private:
			/// The timer's parent Animation.
			Animation* animation_ = nullptr;

			/// The amount of time (in milliseconds) to wait before starting an animation cycle. Defaults to 0.
			uint16_t delay_;

			/// The number of steps from the current cycle to the next cycle.
			uint8_t step_count_ = 1;
	};
}

#endif // ANIMATIONTIMER_H
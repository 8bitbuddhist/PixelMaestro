/*
 * Timing - Classes for managing time-sensitive actions.
 */

#ifndef TIMING_H
#define TIMING_H

#include "stdint.h"

namespace PixelMaestro {
	class Timing {
		public:
			Timing(uint16_t speed = 1000);
			uint16_t get_speed();
			void set_speed(uint16_t speed);
			bool update(const uint32_t& current_time);

		protected:
			/// The amount of time (in milliseconds) since the last event.
			uint32_t last_time_ = 0;

			/// The amount of time (in milliseconds) between events.
			uint16_t speed_;
	};

	class AnimationTiming : public Timing {
		public:
			AnimationTiming(uint16_t speed = 1000, uint16_t pause = 0);
			uint16_t get_pause();
			uint8_t get_step_count();
			void recalculate_step_count(bool fade, uint16_t refresh_interval);
			void set_speed(uint16_t speed, uint16_t pause = 0);

		private:
			/// The amount of time (in milliseconds) to wait before starting an animation cycle. Defaults to 0.
			uint16_t pause_;

			/// The number of steps from the current cycle to the next cycle.
			uint8_t step_count_ = 1;
	};
}

#endif // TIMING_H

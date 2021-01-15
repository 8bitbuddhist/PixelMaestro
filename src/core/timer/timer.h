/*
 * Timer - Class for managing time-sensitive actions.
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

namespace PixelMaestro {
	class Timer {
		public:
			explicit Timer(uint16_t interval = 1000);
			uint16_t get_interval() const;
			uint32_t get_last_time() const;
			bool get_running() const;
			void set_interval(uint16_t interval);
			void set_last_time(uint32_t last_time = 0);
			void start();
			void stop();
			bool update(const uint32_t& current_time);
			static uint16_t upm_to_millis(float upm);
			static float millis_to_upm(uint16_t millis);

		protected:
			/// The amount of time (in milliseconds) since the last event.
			uint32_t last_time_ = 0;

			/// The amount of time (in milliseconds) between events.
			uint16_t interval_ = 1000;

			/// Whether the timer is currently running.
			bool running_ = true;
	};
}

#endif // TIMER_H

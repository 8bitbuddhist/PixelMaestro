/*
 * Timer - Class for managing time-sensitive actions.
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

namespace PixelMaestro {
	class Timer {
		public:
			Timer(uint16_t speed = 1000);
			uint16_t get_interval() const;
			uint32_t get_last_time() const;
			void set_interval(uint16_t interval);
			void set_last_time(uint32_t last_time = 0);
			void start();
			void stop();
			bool update(const uint32_t& current_time);

		protected:
			/// The amount of time (in milliseconds) since the last event.
			uint32_t last_time_ = 0;

			/// The amount of time (in milliseconds) between events.
			uint16_t interval_;

			/// Whether the timer is currently running.
			bool running_ = true;
	};
}

#endif // TIMER_H

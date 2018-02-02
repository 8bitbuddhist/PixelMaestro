/*
 * Timing - Class for managing time-sensitive actions.
 */

#ifndef TIMING_H
#define TIMING_H

#include <stdint.h>

namespace PixelMaestro {
	class Timing {
		public:
			Timing(uint16_t speed = 1000);
			uint16_t get_interval() const;
			uint32_t get_last_time() const;
			void set_interval(uint16_t interval);
			void set_last_time(uint32_t last_time = 0);
			bool update(const uint32_t& current_time);

		protected:
			/// The amount of time (in milliseconds) since the last event.
			uint32_t last_time_ = 0;

			/// The amount of time (in milliseconds) between events.
			uint16_t interval_;
	};
}

#endif // TIMING_H

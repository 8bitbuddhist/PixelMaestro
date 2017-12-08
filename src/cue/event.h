/*
 * Event.h - Base class for Show events.
 */

#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>

namespace PixelMaestro {
	class Event {

		public:
			Event();
			Event(uint32_t time, uint8_t* cue);
			Event(const Event& other);
			Event* operator=(const Event& other);
			~Event();
			uint8_t* get_cue() const;
			uint32_t get_time() const;
			void set_cue(uint8_t* cue);
			void set_time(uint32_t time);

		protected:
			/// The Cue to run.
			uint8_t* cue_ = nullptr;

			/// Time that this Event will run.
			uint32_t time_ = 0;

	};
}

#endif // EVENT_H

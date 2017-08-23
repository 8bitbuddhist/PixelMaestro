/*
 * Event.h - Base class for Show events.
 */

#ifndef EVENT_H
#define EVENT_H

namespace PixelMaestro {
	class Event {

		public:
			Event(unsigned long time);
			unsigned long getTime();
			virtual void run() = 0;
			void setTime(unsigned long time);

		protected:
			/// Time that this Event will run.
			unsigned long time_;

	};
}

#endif // EVENT_H

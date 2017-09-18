#ifndef ANIMATIONSETSPEEDEVENT_H
#define ANIMATIONSETSPEEDEVENT_H

#include "../animation/animation.h"
#include "event.h"

namespace PixelMaestro {
	class AnimationSetSpeedEvent : public Event {
		public:
			AnimationSetSpeedEvent(unsigned long time, Animation* animation, unsigned short speed, unsigned short pause = 0);
			void run();

		private:
			Animation* animation_;
			unsigned short speed_;
			unsigned short pause_;
	};
}

#endif // ANIMATIONSETSPEEDEVENT_H

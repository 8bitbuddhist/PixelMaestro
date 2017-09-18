#ifndef ANIMATIONSETFADEEVENT_H
#define ANIMATIONSETFADEEVENT_H

#include "../core/section.h"
#include "event.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class AnimationSetFadeEvent : public Event {
		public:
			AnimationSetFadeEvent(unsigned long time, Animation* animation, bool fade);
			void run();

		private:
			Animation* animation_;
			bool fade_;
	};
}

#endif // ANIMATIONSETFADEEVENT_H

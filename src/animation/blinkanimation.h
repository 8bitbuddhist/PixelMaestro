#ifndef BLINKANIMATION_H
#define BLINKANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class BlinkAnimation : public MappedAnimation {
		public:
			explicit BlinkAnimation(Section& section);
			~BlinkAnimation() = default;
			void map();
			void update();
	};
}

#endif // BLINKANIMATION_H

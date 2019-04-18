#ifndef CYCLEANIMATION_H
#define CYCLEANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class CycleAnimation : public MappedAnimation {
		public:
			explicit CycleAnimation(Section& section);
			~CycleAnimation() = default;
			void map();
			void update();
	};
}

#endif // CYCLEANIMATION_H

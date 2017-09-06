#ifndef RANDOMANIMATION_H
#define RANDOMANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class RandomAnimation : public ColorAnimation {
		public:
			RandomAnimation(Section* section, bool reverse = false, Orientations orientation = Orientations::HORIZONTAL);
			void update();
	};
}

#endif // RANDOMANIMATION_H

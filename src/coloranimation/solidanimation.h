#ifndef SOLIDANIMATION_H
#define SOLIDANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class SolidAnimation : public ColorAnimation {
		public:
			SolidAnimation(Section* section, bool reverse = false, Orientations orientation = Orientations::HORIZONTAL);
			void update();
	};
}

#endif // SOLIDANIMATION_H

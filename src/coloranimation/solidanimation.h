#ifndef SOLIDANIMATION_H
#define SOLIDANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class SolidAnimation : public ColorAnimation {
		public:
			SolidAnimation(Section *section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();
	};
}

#endif // SOLIDANIMATION_H

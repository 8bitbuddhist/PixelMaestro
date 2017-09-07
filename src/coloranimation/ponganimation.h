#ifndef PONGANIMATION_H
#define PONGANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class PongAnimation : public ColorAnimation {
		public:
			PongAnimation(Section *section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();
	};
}

#endif // PONGANIMATION_H

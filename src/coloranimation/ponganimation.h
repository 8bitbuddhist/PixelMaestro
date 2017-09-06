#ifndef PONGANIMATION_H
#define PONGANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class PongAnimation : public ColorAnimation {
		public:
			PongAnimation(Section* section, bool reverse = false, Orientations orientation = Orientations::HORIZONTAL);
			void update();

		private:
			/// Determines whether the animation is moving forwards or backwards.
			bool ping_ = true;
	};
}

#endif // PONGANIMATION_H

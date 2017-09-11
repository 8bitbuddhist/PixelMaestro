#ifndef PLASMAANIMATION_H
#define PLASMAANIMATION_H

#include "animation.h"

namespace  PixelMaestro {
	class PlasmaAnimation : public Animation {
		public:
			PlasmaAnimation(Section* section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0, float size = 32.0, float resolution = 4.0);
			void update();

		private:
			/// Variables that control the appearance of the plasma.
			float size_, resolution_;
	};
}

#endif // PLASMAANIMATION_H

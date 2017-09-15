#ifndef PLASMAANIMATION_H
#define PLASMAANIMATION_H

#include "animation.h"

namespace  PixelMaestro {
	class PlasmaAnimation : public Animation {
		public:
			PlasmaAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, float size = 4.0, float resolution = 32.0);
			void set_resolution(float resolution);
			void set_size(float size);
			void update(Section* section);

		private:
			/// The resolution of each plasma (i.e. the number of bands).
			float resolution_;

			/// The size of each plasma.
			float size_;
	};
}

#endif // PLASMAANIMATION_H

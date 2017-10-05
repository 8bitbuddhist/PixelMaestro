#ifndef PLASMAANIMATION_H
#define PLASMAANIMATION_H

#include "animation.h"

namespace  PixelMaestro {
	class PlasmaAnimation : public Animation {
		public:
			PlasmaAnimation(Colors::RGB* colors, uint8_t num_colors, float size = 4.0, float resolution = 32.0);
			~PlasmaAnimation();
			float get_resolution();
			float get_size();
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

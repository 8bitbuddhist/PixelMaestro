#ifndef RADIALANIMATION_H
#define RADIALANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class RadialAnimation : public Animation {
		public:
			explicit RadialAnimation(Section& section);
			~RadialAnimation() = default;
			uint8_t get_resolution() const;
			void set_resolution(uint8_t resolution);
			void update();

		private:
			/// In vertical mode, this defines the wideness of each spoke coming from the center.
			uint8_t resolution_ = 10;

			void map();
	};
}

#endif // RADIALANIMATION_H

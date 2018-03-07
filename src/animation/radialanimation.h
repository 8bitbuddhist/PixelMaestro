#ifndef RADIALANIMATION_H
#define RADIALANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class RadialAnimation : public MappedAnimation {
		public:
			explicit RadialAnimation(Section* section);
			~RadialAnimation();
			uint8_t get_resolution() const;
			void set_resolution(uint8_t resolution);
			void update();

		private:
			/// In vertical mode, this defines the wideness of each spoke coming from the center.
			uint8_t resolution_ = 10;

			/// Tracks whether the orientation has changed.
			Animation::Orientation last_orientation_ = Orientation::Horizontal;

			void map();
	};
}

#endif // RADIALANIMATION_H

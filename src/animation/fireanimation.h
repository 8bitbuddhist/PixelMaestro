#ifndef FIREANIMATION_H
#define FIREANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class FireAnimation : public MappedAnimation {
		public:
			FireAnimation(Section* section, Colors::RGB* colors = nullptr, uint8_t num_colors = 0);
			~FireAnimation();
			uint8_t get_multiplier();
			void map();
			void set_multiplier(uint8_t multiplier);
			void update();

		private:
			/// Sets the size of the flames (larger value = bigger flames).
			uint8_t multiplier_ = 48;
	};
}

#endif // FIREANIMATION_H
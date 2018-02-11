#ifndef MERGEANIMATION_H
#define MERGEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class MergeAnimation : public Animation {
		public:
			MergeAnimation(Section* section, Colors::RGB* colors, uint8_t num_colors);
			~MergeAnimation();
			int8_t get_skew();
			void set_skew(int8_t skew);
			void update();

		private:
			/// Counter for the current Pixel index.
			uint16_t count_ = 0;

			///	The amount to offset each row (or column).
			int8_t skew_ = 0;
	};
}


#endif // MERGEANIMATION_H

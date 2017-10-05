#ifndef MERGEANIMATION_H
#define MERGEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class MergeAnimation : public Animation {
		public:
			MergeAnimation(Colors::RGB* colors, uint8_t num_colors);
			~MergeAnimation();
			void update(Section* section);

		private:
			/// Counter for the current Pixel index.
			uint16_t count_ = 0;

			/// Stores the array center.
			uint16_t mid_point_ = 0;
	};
}


#endif // MERGEANIMATION_H

#ifndef MERGEANIMATION_H
#define MERGEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class MergeAnimation : public Animation {
		public:
			MergeAnimation(Colors::RGB* colors = nullptr, uint8_t num_colors = 0, uint16_t speed = 100, uint16_t pause = 0);
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

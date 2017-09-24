#ifndef MERGEANIMATION_H
#define MERGEANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class MergeAnimation : public Animation {
		public:
			MergeAnimation(Colors::RGB* colors = nullptr, unsigned char num_colors = 0, unsigned short speed = 100, unsigned short pause = 0);
			~MergeAnimation();
			void update(Section* section);

		private:
			/// Counter for the current Pixel index.
			unsigned short count_ = 0;

			/// Stores the array center.
			unsigned short mid_point_ = 0;
	};
}


#endif // MERGEANIMATION_H

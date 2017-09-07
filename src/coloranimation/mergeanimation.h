#ifndef MERGEANIMATION_H
#define MERGEANIMATION_H

#include "coloranimation.h"

namespace PixelMaestro {
	class MergeAnimation : public ColorAnimation {
		public:
			MergeAnimation(Section *section, Colors::RGB* colors = nullptr, unsigned short num_colors = 0);
			void update();

		private:
			/// Counter for the current Pixel index.
			unsigned short count_ = 0;

			/// Stores the array center.
			unsigned short mid_point_ = 0;
	};
}


#endif // MERGEANIMATION_H

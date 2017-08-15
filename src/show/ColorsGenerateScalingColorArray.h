#ifndef COLORSGENERATESCALINGCOLORARRAY_H
#define COLORSGENERATESCALINGCOLORARRAY_H

#include "../Colors.h"
#include "Transition.h"

namespace PixelMaestro {
	class ColorsGenerateScalingColorArray : public Transition {
		public:
			ColorsGenerateScalingColorArray(unsigned long time, Colors::RGB newArray[], Colors::RGB *baseColor, Colors::RGB *targetColor, unsigned int numColors, bool reverse);
			ColorsGenerateScalingColorArray(unsigned long time, Colors::RGB newArray[], Colors::RGB *baseColor, unsigned int numColors, unsigned char threshold, bool reverse);
			void run();

		private:
			Colors::RGB *base_color_ = nullptr;
			Colors::RGB *new_array_;
			unsigned int num_colors_;
			bool reverse_;
			Colors::RGB *target_color_ = nullptr;
			unsigned char threshold_;
	};
}

#endif // COLORSGENERATESCALINGCOLORARRAY_H

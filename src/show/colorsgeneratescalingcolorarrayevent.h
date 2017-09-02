#ifndef COLORSGENERATESCALINGCOLORARRAYEVENT_H
#define COLORSGENERATESCALINGCOLORARRAYEVENT_H

#include "../colors.h"
#include "event.h"

namespace PixelMaestro {
	class ColorsGenerateScalingColorArrayEvent : public Event {
		public:
			ColorsGenerateScalingColorArrayEvent(unsigned long time, Colors::RGB new_array[], Colors::RGB* base_color, Colors::RGB* target_color, unsigned int num_colors, bool reverse);
			ColorsGenerateScalingColorArrayEvent(unsigned long time, Colors::RGB new_array[], Colors::RGB* base_color, unsigned int num_colors, unsigned char threshold, bool reverse);
			void run();

		private:
			Colors::RGB* base_color_ = nullptr;
			Colors::RGB* new_array_;
			unsigned int num_colors_;
			bool reverse_;
			Colors::RGB* target_color_ = nullptr;
			unsigned char threshold_;
	};
}

#endif // COLORSGENERATESCALINGCOLORARRAYEVENT_H

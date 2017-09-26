#ifndef ANIMATIONSERIAL_H
#define ANIMATIONSERIAL_H

#include "../animation/animation.h"
#include "../core/colors.h"
#include "../core/maestro.h"

namespace PixelMaestro {
	class AnimationSerial {
		public:
			enum Action {
				SetColors,
				SetCycleIndex,
				SetFade,
				SetOrientation,
				SetReverse,
				SetSpeed
			};

			// TODO: Animation-specific opts
			static void set_colors(unsigned char* buffer, unsigned char section_num, Colors::RGB* colors, unsigned char num_colors);
			static void set_cycle_index(unsigned char* buffer, unsigned char section_num, unsigned char cycle_index);
			static void set_fade(unsigned char* buffer, unsigned char section_num, bool fade);
			static void set_orientation(unsigned char* buffer, unsigned char section_num, Animation::Orientation orientation);
			static void set_reverse(unsigned char* buffer, unsigned char section_num, bool reverse);
			static void set_speed(unsigned char* buffer, unsigned char section_num, unsigned short speed, unsigned short pause);

			static void run(Maestro* maestro, unsigned char* buffer);
	};
}

#endif // ANIMATIONSERIAL_H

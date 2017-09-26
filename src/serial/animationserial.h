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
				SetFade,
				SetSpeed
			};

			static void set_colors(unsigned char* buffer, unsigned char section_num, Colors::RGB* colors, unsigned char num_colors);
			static void set_fade(unsigned char* buffer, unsigned char section_num, bool fade);
			static void set_speed(unsigned char* buffer, unsigned char section_num, unsigned short speed, unsigned short pause);

			static void run(Maestro* maestro, unsigned char* buffer);
	};
}

#endif // ANIMATIONSERIAL_H

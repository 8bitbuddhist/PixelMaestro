#ifndef ANIMATIONSERIAL_H
#define ANIMATIONSERIAL_H

#include "animation/animation.h"
#include "core/maestro.h"

namespace PixelMaestro {
	class AnimationSerial {
		public:
			enum Action {
				SetFade,
				SetSpeed
			};

			static void set_fade(unsigned char* buffer, unsigned char section_num, bool fade);
			static void set_speed(unsigned char* buffer, unsigned char section_num, unsigned short speed, unsigned short pause);

			static void run(Maestro* maestro, unsigned char* buffer);
	};
}

#endif // ANIMATIONSERIAL_H

/*
 * AnimationType - List of available Animations.
 */

#ifndef ANIMATIONTYPE_H
#define ANIMATIONTYPE_H

namespace PixelMaestro {
	class AnimationType {
		public:
			/// The type of animation.
			enum Type : uint8_t {
				Blink,
				Cycle,
				Lightning,
				Mandelbrot,
				Merge,
				Plasma,
				Radial,
				Random,
				Solid,
				Sparkle,
				Wave
			};
	};
}

#endif // ANIMATIONTYPE_H

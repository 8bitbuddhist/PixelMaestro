/*
 * AnimationType - List of available Animations.
 */

#ifndef ANIMATIONTYPE_H
#define ANIMATIONTYPE_H

namespace PixelMaestro {
	class AnimationType {
		public:
			// TODO: Add Wireworld animation: https://en.wikipedia.org/wiki/Wireworld
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

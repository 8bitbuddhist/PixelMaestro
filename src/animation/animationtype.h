#ifndef ANIMATIONTYPE_H
#define ANIMATIONTYPE_H

namespace PixelMaestro {
	class AnimationType {
		public:
			/// The type of animation.
			enum Type {
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

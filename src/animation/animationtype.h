/*
 * AnimationType - List of available Animations.
 */

#ifndef ANIMATIONTYPE_H
#define ANIMATIONTYPE_H

namespace PixelMaestro {
	/// The type of animation.
	enum class AnimationType : uint8_t {
		Blink,
		Cycle,
		Fire,
		Lightning,
		Mandelbrot,
		Plasma,
		Radial,
		Random,
		Solid,
		Sparkle,
		Wave
	};
}

#endif // ANIMATIONTYPE_H

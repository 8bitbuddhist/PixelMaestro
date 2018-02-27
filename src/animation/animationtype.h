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
		Lightning,
		Mandelbrot,
		Plasma,
		Radial,
		Random,
		Solid,
		Sparkle,
		Wave,
		Fire
	};
}

#endif // ANIMATIONTYPE_H

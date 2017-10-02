#include "utility.h"

namespace PixelMaestro {

	// Must initialize static char value in source file.
	int Utility::seed_ = 1;

	/**
	 * Returns the absolute value of an integer.
	 * @param val The integer to evaluate.
	 * @return The absolute value of the integer.
	 */
	uint32_t Utility::abs_int(int32_t val) {
		return val > 0 ? val : -val;
	}

	/**
	 * Generates a pseudo-random integer value.
	 * @param max Max limit of the RNG range.
	 * @return Random integer value.
	 */
	int32_t Utility::rand(int32_t max) {
		seed_ = (seed_ * 1103515245U + 12345U) & 0x7fffffffU;
		if (max == 0) {
			return (int32_t)seed_;
		}
		else {
			return (int32_t)seed_ % max;
		}
	}

	/**
	 * Returns the square root of a number.
	 * @param val Number to evaluate.
	 * @return The square root of the number.
	 */
	float Utility::sqrt(float val) {
		// Fast inverse square root: https://en.wikipedia.org/wiki/Fast_inverse_square_root
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = val * 0.5F;
		y  = val;
		i  = * ( long * ) &y;                     // floating point bit level hacking [sic]
		i  = 0x5f3759df - ( i >> 1 );             // Newton's approximation
		y  = * ( float * ) &i;
		y  = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
		y  = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration
		y  = y * ( threehalfs - ( x2 * y * y ) ); // 3rd iteration

		return 1/y;
	}

	/**
	 * Returns the square of an integer value.
	 * @param val The integer to evaluate.
	 * @return The integer squared.
	 */
	uint32_t Utility::square(int16_t val) {
		return val * val;
	}
}

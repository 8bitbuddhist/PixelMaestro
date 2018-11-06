#include "utility.h"

namespace PixelMaestro {

	// Must initialize static char value in source file.
	int32_t Utility::seed_ = 1;

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
	 * Sets the initial seed for the RNG.
	 * @param seed Intiial value used to generate random numbers.
	 */
	void Utility::srand(int32_t seed) {
		seed_ = seed;
	}
}

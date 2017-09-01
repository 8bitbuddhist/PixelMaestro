#include "utility.h"

namespace PixelMaestro {

	// Must initialize static char value in source file.
	int Utility::seed_ = 1;

	/**
	 * Returns the absolute value of an integer.
	 * @param val The integer to evaluate.
	 * @return The absolute value of the integer.
	 */
	unsigned int Utility::abs_int(short val) {
		return val > 0 ? (unsigned int)val : (unsigned int)-val;
	}

	/**
	 * Generates a pseudo-random integer value.
	 * @return Random integer value.
	 */
	int Utility::rand() {
		seed_ = (seed_ * 1103515245U + 12345U) & 0x7fffffffU;
		return (int)seed_;
	}

	/**
	 * Returns the square of an integer value.
	 * @param val The integer to evaluate.
	 * @return The integer squared.
	 */
	unsigned int Utility::square(short val) {
		return val * val;
	}
}

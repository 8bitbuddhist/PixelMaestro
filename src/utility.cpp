#include "utility.h"

namespace PixelMaestro {

	// Must initialize static char value in source file.
	int Utility::seed_ = 1;

	/**
	 * Returns the absolute value of a number.
	 * @param val The number to evaluate.
	 * @return The absolute value of the number.
	 */
	unsigned int Utility::abs(short val) {
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
}

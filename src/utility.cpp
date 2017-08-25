#include "utility.h"

namespace PixelMaestro {

	// Must initialize static char value in source file.
	int Utility::seed_ = 1;

	/**
	 * Returns the absolute value of a float.
	 * @param val The float to evaluate.
	 * @return The absolute value of the float.
	 */
	float Utility::abs_float(float val) {
		return val > 0 ? (float)val : (float)-val;
	}

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
}

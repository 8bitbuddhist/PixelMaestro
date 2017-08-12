#include "Utility.h"

namespace PixelMaestro {

	int Utility::seed_  = 1;

	unsigned char Utility::abs_char(int val) {
		return val > 0 ? val : -val;
	}

	int Utility::rand() {
		seed_ = (seed_ * 1103515245U + 12345U) & 0x7fffffffU;
		return (int)seed_;
	}
}

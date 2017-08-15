#include "ColorsGenerateRandomColorTransition.h"

namespace PixelMaestro {
	ColorsGenerateRandomColorTransition::ColorsGenerateRandomColorTransition(unsigned long time, Colors::RGB *color) : Transition(time) {
		this->color_ = color;
	}

	void ColorsGenerateRandomColorTransition::run() {
		*this->color_ = Colors::generateRandomColor();
	}
}

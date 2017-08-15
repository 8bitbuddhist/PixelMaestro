#include "ColorsGenerateRandomColorTransition.h"

namespace PixelMaestro {
	ColorsGenerateRandomColorTransition::ColorsGenerateRandomColorTransition(Colors::RGB *color, unsigned long time) : Transition(time) {
		this->color_ = color;
	}

	void ColorsGenerateRandomColorTransition::run() {
		*this->color_ = Colors::generateRandomColor();
	}
}

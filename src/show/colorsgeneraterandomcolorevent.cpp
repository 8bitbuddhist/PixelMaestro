#include "colorsgeneraterandomcolorevent.h"
#include "../utility.h"

namespace PixelMaestro {
	/**
	 * Constructor. Generates a new random Color.
	 * @param time Time to run the Event.
	 * @param color Location to store the generated color.
	 */
	ColorsGenerateRandomColorEvent::ColorsGenerateRandomColorEvent(unsigned long time, Colors::RGB* color) : Event(time) {
		this->color_ = color;
	}

	/**
	 * Constructor. Selects a random Color out of a selection of Colors.
	 * @param time Time to run the Event.
	 * @param color Location to store the selected Color.
	 * @param selection Array to select a random color from.
	 * @param num_options The number of Colors in the selection array.
	 */
	ColorsGenerateRandomColorEvent::ColorsGenerateRandomColorEvent(unsigned long time, Colors::RGB* color, Colors::RGB* selection, unsigned int num_options) : Event(time) {
		this->color_ = color;
		this->num_options_ = num_options;
		this->selection_ = selection;
	}

	void ColorsGenerateRandomColorEvent::run() {
		if (selection_) {
			*color_ = selection_[Utility::rand() % num_options_];
		}
		else {
			*color_ = Colors::generate_random_color();
		}
	}
}

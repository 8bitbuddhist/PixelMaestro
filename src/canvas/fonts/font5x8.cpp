/*
 * font5x8.cpp - 5x8 font courtesy of Roznerd - http://roznerd.blogspot.com/2010/02/led-dot-matrix-pov-font-generator.html
 */

#include "font5x8.h"

namespace PixelMaestro {
	Font5x8::Font5x8() {
		size.set(5, 8);
	}

	uint8_t* Font5x8::get_char(uint8_t character) {
		return font[character - 32];
	}

	Font5x8::~Font5x8() {}
}

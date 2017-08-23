/*
 * font5x8.cpp - 5x8 font courtesy of Roznerd - http://roznerd.blogspot.com/2010/02/led-dot-matrix-pov-font-generator.html
 */

#include "font5x8.h"

namespace PixelMaestro {
	Font5x8::Font5x8() : Font() {
		this->size = new Section::Layout(8, 5);
	}

	unsigned char *Font5x8::getChar(unsigned char character) {
		return this->font[character - 32];
	}
}

/*
 * font5x8.cpp - 5x8 font courtesy of Roznerd - http://roznerd.blogspot.com/2010/02/led-dot-matrix-pov-font-generator.html
 */

#include "font5x8.h"

namespace PixelMaestro {
	Font5x8::Font5x8() : Font() {
		size = new Point(5, 8);
	}

	unsigned char* Font5x8::get_char(unsigned char character) {
		return font[character - 32];
	}
}

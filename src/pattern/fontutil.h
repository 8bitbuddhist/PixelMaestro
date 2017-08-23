/*
 * FontUtil.cpp - Tools for utilizing and interacting with fonts.
 */
#ifndef FONTUTIL_H
#define FONTUTIL_H

#include "fonts/font.h"
#include "../section.h"

namespace PixelMaestro {
	class FontUtil {
		public:
			static void printString(Font *font, bool *frame, Point *patternLayout, const char *string, int numChars);
	};
}

#endif // FONTUTIL_H

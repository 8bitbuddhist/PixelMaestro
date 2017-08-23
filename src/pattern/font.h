#ifndef FONT_H
#define FONT_H

#include "../section.h"

namespace PixelMaestro {
	class Font {
		public:
			static void printChars(bool *frame, Section::Layout *patternLayout, const char *string, int numChars);
	};
}

#endif // FONT_H

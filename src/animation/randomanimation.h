#ifndef RANDOMANIMATION_H
#define RANDOMANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class RandomAnimation : public MappedAnimation {
		public:
			explicit RandomAnimation(Section& section);
			~RandomAnimation() = default;
			void map();
			void update();
	};
}

#endif // RANDOMANIMATION_H

#ifndef RANDOMANIMATION_H
#define RANDOMANIMATION_H

#include "animation.h"

namespace PixelMaestro {
	class RandomAnimation : public Animation {
		public:
			explicit RandomAnimation(Section* section);
			~RandomAnimation() = default;
			void update();
	};
}

#endif // RANDOMANIMATION_H

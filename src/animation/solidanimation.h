#ifndef SOLIDANIMATION_H
#define SOLIDANIMATION_H

#include "mappedanimation.h"

namespace PixelMaestro {
	class SolidAnimation : public MappedAnimation {
		public:
			explicit SolidAnimation(Section& section);
			~SolidAnimation() = default;
			void map();
			void update();
	};
}

#endif // SOLIDANIMATION_H

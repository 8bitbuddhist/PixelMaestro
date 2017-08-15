#ifndef SECTIONUNSETOVERLAYTRANSITION_H
#define SECTIONUNSETOVERLAYTRANSITION_H

#include "../Section.h"
#include "Transition.h"

namespace PixelMaestro {
	class SectionUnsetOverlayTransition : public Transition {
		public:
			SectionUnsetOverlayTransition(unsigned long time, Section *section);
			void run();

		private:
			Section *section_;
	};
}

#endif // SECTIONUNSETOVERLAYTRANSITION_H

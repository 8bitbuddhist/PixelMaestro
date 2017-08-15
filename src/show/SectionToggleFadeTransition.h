#ifndef SECTIONTOGGLEFADINGTRANSITION_H
#define SECTIONTOGGLEFADINGTRANSITION_H

#include "../Section.h"
#include "Transition.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	class SectionToggleFadeTransition : public Transition {
		public:
			SectionToggleFadeTransition(unsigned long time, Section *section);
			void run();

		private:
			Section *section_;
	};
}

#endif // SECTIONTOGGLEFADINGTRANSITION_H

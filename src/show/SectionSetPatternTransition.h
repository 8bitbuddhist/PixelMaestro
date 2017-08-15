#ifndef SECTIONSETPATTERNTRANSITION_H
#define SECTIONSETPATTERNTRANSITION_H

#include "../Section.h"
#include "Transition.h"

namespace PixelMaestro {
	class SectionSetPatternTransition : public Transition {
		public:
			SectionSetPatternTransition(unsigned long time, Section *section, Section::Pattern *pattern);
			void run();

		private:
			Section::Pattern *pattern_;
			Section *section_;
	};
}

#endif // SECTIONSETPATTERNTRANSITION_H

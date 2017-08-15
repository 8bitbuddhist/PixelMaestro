#ifndef SECTIONSETOVERLAYTRANSITION_H
#define SECTIONSETOVERLAYTRANSITION_H

#include "../Colors.h"
#include "../Section.h"
#include "Transition.h"

namespace PixelMaestro {
	class SectionSetOverlayTransition : public Transition {
		public:
			SectionSetOverlayTransition(unsigned long time, Section *section, Section *overlay, Colors::MixMode mixMode, float alpha = 0.0);
			void run();

		private:
			float alpha_;
			Colors::MixMode mix_mode_;
			Section *overlay_;
			Section *section_;
	};
}

#endif // SECTIONSETOVERLAYTRANSITION_H

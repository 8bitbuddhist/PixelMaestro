#ifndef TOGGLERUNTRANSITION_H
#define TOGGLERUNTRANSITION_H

#include "../Maestro.h"
#include "Transition.h"

namespace PixelMaestro {
	class MaestroToggleRunTransition : public Transition {

		public:
			MaestroToggleRunTransition(Maestro *maestro, unsigned long time);
			void run();

		private:
			Maestro *maestro_;
	};
}

#endif // TOGGLERUNTRANSITION_H

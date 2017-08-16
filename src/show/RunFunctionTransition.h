#ifndef RUNFUNCTIONTRANSITION_H
#define RUNFUNCTIONTRANSITION_H

#include <functional>
#include "Transition.h"

using namespace std;

namespace PixelMaestro {
	class RunFunctionTransition : public Transition {
		public:
			RunFunctionTransition(unsigned long time, function<void()> action);
			void run();

		private:
			function<void()> action_;
	};
}

#endif // RUNFUNCTIONTRANSITION_H

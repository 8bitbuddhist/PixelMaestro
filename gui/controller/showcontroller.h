/*
 * ShowController - Wrapper class for managing a Show.
 */

#ifndef SHOWCONTROLLER_H
#define SHOWCONTROLLER_H

#include "Maestro.h"
#include "maestrocontroller.h"
#include "Show.h"
#include <vector>

using namespace PixelMaestro;

class ShowController {
	public:
		ShowController(MaestroController *maestro);
		void setTransitions(Transition *transitions, unsigned int numTransitions);

	private:
		MaestroController *maestro_ = nullptr;
		Show show_;
		std::vector<Transition> transitions_;
};

#endif // SHOWCONTROLLER_H

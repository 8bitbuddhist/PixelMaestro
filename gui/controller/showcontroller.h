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
		void setTransitions(Show::Transition *transitions, unsigned int numTransitions);

	private:
		MaestroController *maestro_;
		Show show_;
		std::vector<Show::Transition> transitions_;
};

#endif // SHOWCONTROLLER_H

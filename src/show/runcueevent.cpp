#include "runcueevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Runs a Command on a Maestro.
	 * @param time Time until the Event runs.
	 * @param maestro Maestro to run the Command on.
	 * @param cue Cue to run. The contents of the Cue get copied to the Event, so you can safely delete the original.
	 */
	RunCueEvent::RunCueEvent(unsigned long time, Maestro* maestro, unsigned char *cue) : Event(time) {
		maestro_ = maestro;

		// Initialize and copy the Cue over.
		unsigned int size = cue[Cue::Bit::SizeBit] + Cue::Bit::PayloadBit;

		// Create and populate the new Cue buffer.
		cue_ = new unsigned char[size];
		for (unsigned char i = 0; i < size; i++) {
			cue_[i] = cue[i];
		}
	}

	void RunCueEvent::run() {
		Cue::run(maestro_, cue_);
	}

	RunCueEvent::~RunCueEvent() {
		delete[] cue_;
	}
}

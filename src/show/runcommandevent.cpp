#include "runcommandevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Runs a Command on a Maestro.
	 * @param time Time until the Event runs.
	 * @param maestro Maestro to run the Command on.
	 * @param buffer Command to run.
	 */
	RunCommandEvent::RunCommandEvent(unsigned long time, Maestro* maestro, unsigned char *buffer) : Event(time) {
		maestro_ = maestro;

		// Initialize and copy the command over.
		unsigned int packet_size = buffer[Cue::size_index_] + Cue::payload_index_;
		buffer_ = new unsigned char[packet_size];
		for (unsigned char i = 0; i < packet_size; i++) {
			buffer_[i] = buffer[i];
		}
	}

	void RunCommandEvent::run() {
		Cue::run(maestro_, buffer_);
	}

	RunCommandEvent::~RunCommandEvent() {
		delete[] buffer_;
	}
}

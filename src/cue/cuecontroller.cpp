#include "animationcue.h"
#include "canvascue.h"
#include "cuecontroller.h"
#include "maestrocue.h"
#include "sectioncue.h"

namespace PixelMaestro {

	const unsigned char CueController::header_[] = "PMC";

	CueController::CueController(Maestro* maestro, Component* components, unsigned char num_components) {
		maestro_ = maestro;
		set_handlers(components, num_components);
	}

	/**
	 * Adds header info to a Cue.
	 * @param buffer Container for the Cue.
	 * @param payload_size The size of the payload.
	 */
	void CueController::assemble(unsigned char* buffer, unsigned char payload_size) {
		/*
		 * Final Cue has the following form: [Header] [Checksum] [Size] [Payload]
		 *
		 * [Header] is a unique identifier confirming that this is a PixelMaestro Cue (hence PMC).
		 * [Size] is the size of the payload.
		 * [Checksum] is a value generated for error detection.
		 * [Payload] contains the actual command with parameters.
		 */

		for (unsigned char i = 0; i < Bit::ChecksumBit; i++) {
			buffer[i] = header_[i];
		}

		buffer[Bit::SizeBit] = payload_size;

		buffer[Bit::ChecksumBit] = checksum(buffer, Bit::PayloadBit + payload_size);

		// Add null terminator to end of buffer
		buffer[Bit::PayloadBit + payload_size] = '\0';
	}

	/**
	 * Generates a checksum for verifying the integrity of a Cue.
	 * @param buffer The contents of the Cue.
	 * @param buffer_size The size of the Cue.
	 * @return New checksum.
	 */
	unsigned char CueController::checksum(unsigned char *buffer, unsigned char buffer_size) {
		unsigned int sum = 0;
		for (unsigned char i = 0; i < buffer_size; i++) {

			// Make sure we don't include the checksum in its own calculation
			if (i != Bit::ChecksumBit) {
				sum += buffer[i];
			}
		}

		return (sum % 256);
	}

	unsigned char* CueController::get_buffer() {
		return buffer;
	}

	Cue* CueController::get_handler(Component component) {
		if (handlers_[(int)component] != nullptr) {
			return handlers_[(int)component];
		}
		return nullptr;
	}

	/**
	 * Loads a raw Cue into the buffer.
	 * @param cue Cue to load.
	 */
	void CueController::load(unsigned char *cue) {
		// First, verify the header.
		for (unsigned char i = 0; i < Bit::ChecksumBit; i++) {
			if (cue[i] != header_[i]) {
				return;
			}
		}

		unsigned char size = cue[Bit::SizeBit] + Bit::PayloadBit;

		// Second, generate and compare the checksum.
		if (cue[Bit::ChecksumBit] != checksum(cue, size)) {
			return;
		}

		// Finally, load the Cue into the local buffer.
		for (unsigned char i = 0; i < size; i++) {
			buffer[i] = cue[i];
		}
	}

	/**
	 * Runs the current buffer.
	 * @param maestro The Maestro to run the command against.
	 * @param cue The Cue to run.
	 */
	void CueController::run() {
		// Finally, hand off the payload to the appropriate controller.
		handlers_[buffer[Bit::PayloadBit]]->run(buffer);
	}

	void CueController::set_handlers(Component *components, unsigned char num_components) {
		for (unsigned char i = 0; i < num_components; i++) {
			switch(components[i]) {
				case AnimationComponent:
					handlers_[(int)Component::AnimationComponent] = new AnimationCue(maestro_, buffer);
					break;
				case CanvasComponent:
					handlers_[(int)Component::CanvasComponent] = new CanvasCue(maestro_, buffer);
					break;
				case MaestroComponent:
					handlers_[(int)Component::MaestroComponent] = new MaestroCue(maestro_, buffer);
					break;
				case SectionComponent:
					handlers_[(int)Component::SectionComponent] = new SectionCue(maestro_, buffer);
					break;
			}
		}
	}
}

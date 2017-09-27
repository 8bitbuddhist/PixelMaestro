#include "animationcue.h"
#include "canvascue.h"
#include "cue.h"
#include "maestrocue.h"
#include "sectioncue.h"

namespace PixelMaestro {

	const unsigned char Cue::header_len_ = 3;
	const unsigned char Cue::header_[] = "PMC";
	unsigned char Cue::checksum_index_ = header_len_;
	unsigned char Cue::size_index_ = checksum_index_ + 1;
	unsigned char Cue::payload_index_ = size_index_ + 1;

	/**
	 * Assembles a payload into a complete Cue.
	 * @param buffer Container for the Cue.
	 * @param payload The actual command.
	 * @param payload_size The size of the command.
	 */
	void Cue::assemble(unsigned char* buffer, unsigned char* payload, unsigned char payload_size) {
		/*
		 * Final Cue has the following form: [Header] [Checksum] [Size] [Payload]
		 *
		 * [Header] is a unique identifier confirming that this is a PixelMaestro Cue (hence PMC).
		 * [Size] is the size of the payload.
		 * [Checksum] is a value generated for error detection.
		 * [Payload] contains the actual command with parameters.
		 */

		for (unsigned char i = 0; i < header_len_; i++) {
			buffer[i] = header_[i];
		}

		buffer[size_index_] = payload_size;

		for (unsigned char i = 0; i < payload_size; i++) {
			buffer[payload_index_ + i] = payload[i];
		}

		buffer[checksum_index_] = checksum(buffer, payload_index_ + payload_size);

		// Add null terminator to end of buffer
		buffer[payload_index_ + payload_size] = '\0';
	}

	/**
	 * Generates a checksum for verifying the integrity of a Cue.
	 * @param buffer The contents of the Cue.
	 * @param buffer_size The size of the Cue.
	 * @return New checksum.
	 */
	unsigned char Cue::checksum(unsigned char *buffer, unsigned char buffer_size) {
		unsigned int sum = 0;
		for (unsigned char i = 0; i < buffer_size; i++) {

			// Make sure we don't include the checksum in its own calculation
			if (i != checksum_index_) {
				sum += buffer[i];
			}
		}

		return (sum % 256);
	}

	/**
	 * Parses and executes an incoming Cue.
	 * @param maestro The Maestro to run the command against.
	 * @param cue The Cue to run.
	 */
	void Cue::run(Maestro* maestro, unsigned char *cue) {
		// First, verify the header.
		for (unsigned char i = 0; i < header_len_; i++) {
			if (cue[i] != header_[i]) {
				return;
			}
		}

		// Second, generate and compare the checksum.
		if (cue[checksum_index_] != checksum(cue, cue[size_index_] + payload_index_)) {
			return;
		}

		// Finally, hand off the payload to the appropriate controller.
		switch ((Component)cue[payload_index_]) {
			case Component::Animation:
				AnimationCue::run(maestro, cue);
				break;
			case Component::Canvas:
				CanvasCue::run(maestro, cue);
				break;
			case Component::Maestro:
				MaestroCue::run(maestro, cue);
				break;
			case Component::Section:
				SectionCue::run(maestro, cue);
				break;
		}
	}
}

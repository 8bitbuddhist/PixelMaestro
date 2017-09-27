#include "animationcommand.h"
#include "canvascommand.h"
#include "command.h"
#include "maestrocommand.h"
#include "sectioncommand.h"

namespace PixelMaestro {

	// Initialize header contents
	const unsigned char Command::header_[] = {'P', 'M'};

	void Command::build_packet(unsigned char* buffer, unsigned char* data, unsigned char data_size) {
		/*
		 * Packets take the following form: [Header] [Size] [Checksum] [Payload]
		 *
		 * [Header] is a unique identifier used to confirm that this is a PixelMaestro packet.
		 * [Size] is the size of the payload.
		 * [Checksum] is a value calculated to confirm that the data was transmitted successfully.
		 * [Payload] contains the actual command parameters.
		 */

		// Append header info first
		for (unsigned char i = 0; i < header_len_; i++) {
			buffer[i] = header_[i];
		}

		buffer[size_index_] = data_size;

		// Append the actual data
		for (unsigned char i = 0; i < data_size; i++) {
			buffer[payload_index_ + i] = data[i];
		}

		buffer[checksum_index_] = checksum(buffer, buffer[size_index_] + payload_index_);
	}

	unsigned char Command::checksum(unsigned char *data, unsigned char data_size) {
		unsigned int sum = 0;
		for (unsigned char i = 0; i < data_size; i++) {

			// Make sure we don't include the checksum in its own calculation
			if (i != checksum_index_) {
				sum += data[i];
			}
		}

		return (sum % 256);
	}

	/**
	 * Parses and executes an incoming command.
	 * @param maestro The Maestro to run the command against.
	 * @param command The command to run.
	 */
	void Command::run(Maestro* maestro, unsigned char *command) {
		// First, make sure the header is present
		for (unsigned char i = 0; i < header_len_; i++) {
			if (command[i] != header_[i]) {
				return;
			}
		}

		// Second, generate and compare the checksum
		if (command[checksum_index_] != checksum(command, command[size_index_] + payload_index_)) {
			return;
		}

		// Finally, hand off the command to the appropriate controller
		switch ((Component)command[payload_index_]) {
			case Component::Animation:
				AnimationCommand::run(maestro, command);
				break;
			case Component::Canvas:
				CanvasCommand::run(maestro, command);
				break;
			case Component::Maestro:
				MaestroCommand::run(maestro, command);
				break;
			case Component::Section:
				SectionCommand::run(maestro, command);
				break;
		}
	}
}

#include "animationcommand.h"
#include "canvascommand.h"
#include "command.h"
#include "maestrocommand.h"
#include "sectioncommand.h"

namespace PixelMaestro {

	const unsigned char Command::header_len_ = 2;
	const unsigned char Command::header_[] = {'P', 'M'};
	unsigned char Command::checksum_index_ = header_len_;
	unsigned char Command::size_index_ = checksum_index_ + 1;
	unsigned char Command::payload_index_ = size_index_ + 1;

	/**
	 * Assembles a payload into a packet.
	 * If packet assembly is disabled, then this only appends the payload and its size.
	 * Every Command begins with with the size of its payload.
	 * @param buffer Container for the packet.
	 * @param payload The actual contents of the command.
	 * @param payload_size The size of the command.
	 */
	void Command::assemble(unsigned char* buffer, unsigned char* payload, unsigned char payload_size) {
		/*
		 * Final command has the following form: [Header] [Checksum] [Size] [Payload]
		 *
		 * [Header] is a "unique" identifier confirming that this is a PixelMaestro command.
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
	}

	/**
	 * Generates a checksum for verifying the integrity of a packet.
	 * @param buffer The contents of the packet.
	 * @param buffer_size The size of the packet.
	 * @return New checksum.
	 */
	unsigned char Command::checksum(unsigned char *buffer, unsigned char buffer_size) {
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
	 * Parses and executes an incoming command.
	 * @param maestro The Maestro to run the command against.
	 * @param command The command to run.
	 */
	void Command::run(Maestro* maestro, unsigned char *command) {
		// First, verify the header.
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

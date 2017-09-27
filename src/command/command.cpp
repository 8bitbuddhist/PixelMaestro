#include "animationcommand.h"
#include "canvascommand.h"
#include "command.h"
#include "maestrocommand.h"
#include "sectioncommand.h"

namespace PixelMaestro {

	bool Command::assemble_packets_ = true;
	const unsigned char Command::header_[] = {'P', 'M'};
	unsigned char Command::size_index_ = header_len_;
	unsigned char Command::checksum_index_ = size_index_ + 1;
	unsigned char Command::payload_index_ = checksum_index_ + 1;

	/**
	 * Assembles a payload into a packet.
	 * @param buffer Container for the packet.
	 * @param payload The actual contents of the command.
	 * @param payload_size The size of the command.
	 */
	void Command::assemble(unsigned char* buffer, unsigned char* payload, unsigned char payload_size) {
		// Append the payload first.
		for (unsigned char i = 0; i < payload_size; i++) {
			buffer[payload_index_ + i] = payload[i];
		}

		if (assemble_packets_) {
			/*
			 * Final command has the following form: [Header] [Size] [Checksum] [Payload]
			 *
			 * [Header] is a "unique" identifier confirming that this is a PixelMaestro command.
			 * [Size] is the size of the payload.
			 * [Checksum] is a value calculated to confirm data integrity.
			 * [Payload] contains the actual command with parameters.
			 */

			for (unsigned char i = 0; i < header_len_; i++) {
				buffer[i] = header_[i];
			}

			buffer[size_index_] = payload_size;

			buffer[checksum_index_] = checksum(buffer, buffer[size_index_] + payload_index_);
		}
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
	 * Sets whether commands are automatically encapsulated into packets.
	 * This is useful if sending commands out via Serial.
	 * @param assemble If true, commands are assembled into packets.
	 */
	void Command::set_assemble_packets(bool assemble) {
		if (assemble) {
			assemble_packets_  = true;
			payload_index_ = 5;
		}
		else {
			assemble_packets_ = false;
			payload_index_ = 0;
		}
	}

	/**
	 * Parses and executes an incoming command.
	 * @param maestro The Maestro to run the command against.
	 * @param command The command to run.
	 */
	void Command::run(Maestro* maestro, unsigned char *command) {

		if (assemble_packets_) {
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

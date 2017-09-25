#include "command.h"

namespace PixelMaestro {
	/**
	 * Serializes a command for sending to another Maestro.
	 * @param action Action to perform.
	 * @param args Arguments to send.
	 */
	Command::Command(Action action, unsigned int args[]) {
		// Build the command based on the parameters provided.
		switch(action) {
			case MaestroChangeRefreshInterval: // Format: [Action] [Refresh Rate (1)] [Refresh Rate (2)]
				{
					IntByteConvert::IntAsByte byte = IntByteConvert::int_to_byte(args[0]);
					command_ = new unsigned char[3] {
						MaestroChangeRefreshInterval,
						byte.quotient,
						byte.remainder
					};
				}
				break;
			case SectionAddCanvas: // Format: [Action] [Section ID] [Canvas::CanvasType]
				command_ = new unsigned char[3] {
					SectionAddCanvas,
					(unsigned char)args[0],
					(unsigned char)args[1]
				};
				break;
		}
	}

	unsigned char* Command::get_command() {
		return command_;
	}

	unsigned short Command::get_length() {
		return length_;
	}

	/**
	 * Unparses and runs a serialized Command.
	 * @param maestro The Maestro to run the command against.
	 * @param command The command to run.
	 */
	void Command::run(Maestro* maestro, unsigned char *command) {
		switch (command[0]) {
			case MaestroChangeRefreshInterval:
				maestro->set_refresh_interval(IntByteConvert::byte_to_int(command[1], command[2]));
				break;
			case SectionAddCanvas:
				maestro->get_section(command[1])->add_canvas(CanvasType::Type(command[2]));
				break;
		}
	}
}

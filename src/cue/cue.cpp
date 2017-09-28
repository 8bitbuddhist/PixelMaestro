#include "cue.h"

namespace PixelMaestro {
	Cue::Cue(Maestro* maestro, unsigned char* buffer)	{
		maestro_ = maestro;
		buffer_ = buffer;
	}

	// TODO: Dynamic or static buffer?
	void Cue::initialize_buffer(unsigned char size) {
		delete[] buffer_;
		buffer_ = new unsigned char[size];

		/*
		for (unsigned char i = 0; i < size; i++) {
			buffer_[i] = buffer[i];
		}
		*/
	}
}

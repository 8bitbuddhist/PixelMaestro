#include "cuecontroller.h"
#include "animationcuehandler.h"
#include "canvascuehandler.h"
#include "maestrocuehandler.h"
#include "sectioncuehandler.h"

namespace PixelMaestro {

	/**
	 * Constructor.
	 * @param maestro Maestro that processed Cues will run on.
	 */
	CueController::CueController(Maestro* maestro) {
		maestro_ = maestro;
	}

	/**
	 * Prepares the Cue for transport by adding header info.
	 * @param payload_size The size of the payload.
	 */
	void CueController::assemble(unsigned char payload_size) {
		/*
		 * Final Cue has the following form: [Header] [Checksum] [Size] [Payload]
		 *
		 * [Header] is a unique identifier confirming that this is a PixelMaestro Cue (hence PMC).
		 * [Size] is the size of the payload.
		 * [Checksum] is a value generated for error detection.
		 * [Payload] contains the actual command with parameters.
		 */

		for (unsigned char i = 0; i < Byte::ChecksumByte; i++) {
			cue_[i] = header_[i];
		}

		cue_[Byte::SizeByte] = payload_size;

		cue_[Byte::ChecksumByte] = checksum(cue_, Byte::PayloadByte + payload_size);
	}

	/**
	 * Generates a checksum for verifying the integrity of a Cue.
	 * @param cue The contents of the Cue.
	 * @param cue_size The size of the Cue.
	 * @return New checksum.
	 */
	unsigned char CueController::checksum(unsigned char *cue, unsigned char cue_size) {
		unsigned int sum = 0;
		for (unsigned char i = 0; i < cue_size; i++) {

			// Make sure we don't include the checksum in its own calculation
			if (i != Byte::ChecksumByte) {
				sum += cue[i];
			}
		}

		return (sum % 256);
	}

	/**
	 * Enables the specified CueHandler.
	 * @param handler CueHandler to enable.
	 * @return New CueHandler.
	 */
	CueHandler* CueController::enable_handler(Handler handler) {
		if (handlers_[(int)handler] == nullptr) {
			switch(handler) {
				case AnimationHandler:
					handlers_[(int)Handler::AnimationHandler] = new AnimationCueHandler(this);
					break;
				case CanvasHandler:
					handlers_[(int)Handler::CanvasHandler] = new CanvasCueHandler(this);
					break;
				case MaestroHandler:
					handlers_[(int)Handler::MaestroHandler] = new MaestroCueHandler(this);
					break;
				case SectionHandler:
					handlers_[(int)Handler::SectionHandler] = new SectionCueHandler(this);
					break;
			}
		}

		return handlers_[(int)handler];
	}

	/**
	 * Returns the current Cue.
	 * @return Cue buffer.
	 */
	unsigned char* CueController::get_cue() {
		return cue_;
	}

	/**
	 * Returns the size of the currently loaded Cue.
	 * @return Cue size.
	 */
	unsigned char CueController::get_cue_size() {
		return (cue_[Byte::SizeByte] + Byte::PayloadByte);
	}

	/**
	 * Returns the instance of the specified Handler.
	 * @param handler Handler to get.
	 * @return Handler instance.
	 */
	CueHandler* CueController::get_handler(Handler handler) {
		if (handlers_[(int)handler] != nullptr) {
			return handlers_[(int)handler];
		}
		return nullptr;
	}

	/**
	 * Returns the controller's Maestro.
	 * @return Maestro controlling this CueController.
	 */
	Maestro* CueController::get_maestro() {
		return maestro_;
	}

	/**
	 * Loads and runs a raw Cue.
	 * @param cue Cue to load.
	 */
	void CueController::load(unsigned char *cue) {
		// First, verify the header.
		for (unsigned char i = 0; i < Byte::ChecksumByte; i++) {
			if (cue[i] != header_[i]) {
				return;
			}
		}

		unsigned char size = cue[Byte::SizeByte] + Byte::PayloadByte;

		// Second, generate and compare the checksum.
		if (cue[Byte::ChecksumByte] != checksum(cue, size)) {
			return;
		}

		// Next, load the Cue into the local buffer.
		for (unsigned char i = 0; i < size; i++) {
			cue_[i] = cue[i];
		}

		// Finally, run the Cue.
		run();
	}

	/**
	 * Loads and executes multiple Cues sequentially.
	 * @param cues Cues to load.
	 * @param num_cues Number of Cues to load.
	 */
	void CueController::load(unsigned char *cues, unsigned char num_cues) {
		for (unsigned char i = 0; i < num_cues; i++) {
			load(&cues[i]);
		}
	}

	/**
	 * Reads a Cue byte-by-byte into the buffer.
	 * Once the end of the Cue has been reached, the Cue runs and the reader resets for the next Cue.
	 * @param byte Byte to read into the buffer.
	 */
	void CueController::read(unsigned char byte) {
		cue_[read_index_] = byte;

		/*
		 * Run the Cue if once we've read past the payload, then reset the read index.
		 * We re-initialize the read index in the following cases:
		 *	1) If we successfully ran the Cue
		 *	2) If the last bytes read match the header
		 *	3) If we've exceeded the buffer size
		 */
		if (read_index_ > Byte::SizeByte && read_index_ > cue_[Byte::SizeByte]) {
			run();
			read_index_ = 0;
		}
		else {
			if (read_index_ >= Header3Byte &&
				(cue_[read_index_ - Header3Byte] == header_[Header1Byte] &&
				 cue_[read_index_ - Header2Byte] == header_[Header2Byte] &&
				 cue_[read_index_ - Header1Byte] == header_[Header3Byte])) {

				cue_[Header1Byte] = header_[Header1Byte];
				cue_[Header2Byte] = header_[Header2Byte];
				cue_[Header3Byte] = header_[Header3Byte];
				read_index_ = Header3Byte + 1;
			}
			else if ((signed short)(read_index_ + 1) >= 256) {
				read_index_ = 0;
			}
		}
	}

	/**
	 * Runs the currently loaded Cue.
	 * @param maestro The Maestro to run the command against.
	 * @param cue The Cue to run.
	 */
	void CueController::run() {
		handlers_[cue_[Byte::PayloadByte]]->run(cue_);
	}

	CueController::~CueController() {
		for (unsigned char i = 0; i < 4; i++) {
			delete handlers_[i];
		}
	}
}

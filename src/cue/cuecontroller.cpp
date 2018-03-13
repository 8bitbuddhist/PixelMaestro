/*
 * CueController - Class for converting PixelMaestro commands to and from serialized strings.
 */

#include "cuecontroller.h"
#include "animationcuehandler.h"
#include "canvascuehandler.h"
#include "maestrocuehandler.h"
#include "sectioncuehandler.h"
#include "showcuehandler.h"

namespace PixelMaestro {

	/**
	 * Constructor.
	 * @param maestro Maestro that processed Cues will run on.
	 * @param buffer_size The size of the Cue buffer (defaults to 256).
	 */
	CueController::CueController(Maestro* maestro, uint16_t buffer_size) {
		this->maestro_ = maestro;
		this->buffer_size_ = buffer_size;
		this->buffer_ = new uint8_t[buffer_size] {0};
	}

	/**
	 * Prepares the Cue for transport by adding header info.
	 * @param payload_size The size of the payload.
	 * @return Assembled Cue.
	 */
	uint8_t* CueController::assemble(uint16_t payload_size) {
		/*
		 * Final Cue has the following form: [ID] [Checksum] [Size] [Payload]
		 *
		 * [ID] is a set of pre-defined characters marking the start of a Cue.
		 * [Size] is the size of the payload.
		 * [Checksum] is a value generated for error detection.
		 * [Payload] contains the actual command with parameters.
		 */

		for (uint8_t i = 0; i < (uint8_t)Byte::ChecksumByte; i++) {
			buffer_[i] = id_[i];
		}

		IntByteConvert size(payload_size);
		buffer_[(uint8_t)Byte::SizeByte1] = size.converted_0;
		buffer_[(uint8_t)Byte::SizeByte2] = size.converted_1;

		buffer_[(uint8_t)Byte::ChecksumByte] = checksum(buffer_, (uint8_t)Byte::PayloadByte + payload_size);

		return buffer_;
	}

	/**
	 * Generates a checksum for verifying the integrity of a Cue.
	 * Calculated by summing each byte in the Cue, diving by 256, and taking the remainder.
	 * @param cue The contents of the Cue.
	 * @param cue_size The size of the Cue.
	 * @return New checksum.
	 */
	uint8_t CueController::checksum(uint8_t *cue, uint16_t cue_size) {
		uint32_t sum = 0;
		for (uint16_t i = 0; i < cue_size; i++) {

			// Make sure we don't include the checksum in its own calculation
			if (i != (uint8_t)Byte::ChecksumByte) {
				sum += cue[i];
			}
		}

		return (sum % 256);
	}

	/**
	 * Enables the specified CueHandler, or returns the CueHandler if it already exists.
	 * @param handler CueHandler to enable.
	 * @return CueHandler instance.
	 */
	CueHandler* CueController::enable_handler(Handler handler) {
		if (handlers_[(uint8_t)handler] == nullptr) {
			switch(handler) {
				case Handler::AnimationHandler:
					handlers_[(uint8_t)Handler::AnimationHandler] = new AnimationCueHandler(this);
					break;
				case Handler::CanvasHandler:
					handlers_[(uint8_t)Handler::CanvasHandler] = new CanvasCueHandler(this);
					break;
				case Handler::MaestroHandler:
					handlers_[(uint8_t)Handler::MaestroHandler] = new MaestroCueHandler(this);
					break;
				case Handler::SectionHandler:
					handlers_[(uint8_t)Handler::SectionHandler] = new SectionCueHandler(this);
					break;
				case Handler::ShowHandler:
					handlers_[(uint8_t)Handler::ShowHandler] = new ShowCueHandler(this);
					break;
			}
		}

		return handlers_[(uint8_t)handler];
	}

	/**
	 * Returns the currently cached Cue.
	 * @return Cue buffer.
	 */
	uint8_t* CueController::get_buffer() const {
		return buffer_;
	}

	/**
	 * Returns the size of the Cue buffer.
	 * @return Buffer size.
	 */
	uint16_t CueController::get_buffer_size() const {
		return buffer_size_;
	}

	/**
	 * Returns the size of the currently cached Cue.
	 * @return Cue size.
	 */
	uint16_t CueController::get_cue_size() const {
		return (IntByteConvert::byte_to_int(&buffer_[(uint8_t)CueController::Byte::SizeByte1]) + (uint8_t)Byte::PayloadByte);
	}

	/**
	 * Returns the size of the specified Cue.
	 * @param cue Cue to measure.
	 * @return Cue size.
	 */
	uint16_t CueController::get_cue_size(uint8_t *cue) const {
		return (IntByteConvert::byte_to_int(&cue[(uint8_t)CueController::Byte::SizeByte1]) + (uint8_t)Byte::PayloadByte);
	}

	/**
	 * Returns the instance of the specified Handler.
	 * @param handler Handler to get.
	 * @return Handler instance.
	 */
	CueHandler* CueController::get_handler(Handler handler) const {
		return handlers_[(uint8_t)handler];
	}

	/**
	 * Returns the controller's Maestro.
	 * @return Maestro controlling this CueController.
	 */
	Maestro* CueController::get_maestro() const {
		return maestro_;
	}

	/**
	 * Reads a Cue byte-by-byte into the buffer.
	 * Once the end of the Cue has been reached, the Cue runs and the reader resets for the next Cue.
	 * @param byte Byte to read into the buffer.
	 * @return True if the Cue was successfully executed.
	 */
	bool CueController::read(uint8_t byte) {
		buffer_[read_index_] = byte;
		read_index_++;

		/*
		 * Check the current read index.
		 * If we've reached the end of the payload, run the Cue then reset the read index.
		 *
		 * We manually set the read index in the following cases:
		 *	1) If we successfully ran the last Cue, set the index to 0 (start a new Cue)
		 *	2) If the last bytes read match the Cue ID string BUT are not part of the `ShowCueHandler::set_events` Cue, move the ID and read index to the start of the buffer (reduces the chance of a buffer overflow / split Cue)
		 *	3) If we've reached the buffer size limit, set the index to 0 (error / invalid Cue)
		 */
		if (read_index_ >= IntByteConvert::byte_to_int(&buffer_[(uint8_t)Byte::SizeByte1]) + (uint8_t)Byte::PayloadByte) {
			run(buffer_);
			read_index_ = 0;
			return true;
		}
		else {
			// TODO: Make this more readable
			if (read_index_ > (uint8_t)Byte::ID3Byte &&
				(buffer_[(uint8_t)Byte::PayloadByte] == (uint8_t)Handler::ShowHandler && buffer_[(uint8_t)ShowCueHandler::Byte::ActionByte] != (uint8_t)ShowCueHandler::Action::SetEvents) &&
				(buffer_[read_index_ - (uint8_t)Byte::ID3Byte] == id_[(uint8_t)Byte::ID1Byte] &&
				 buffer_[read_index_ - (uint8_t)Byte::ID2Byte] == id_[(uint8_t)Byte::ID2Byte] &&
				 buffer_[read_index_] == id_[(uint8_t)Byte::ID3Byte])) {

				buffer_[(uint8_t)Byte::ID1Byte] = id_[(uint8_t)Byte::ID1Byte];
				buffer_[(uint8_t)Byte::ID2Byte] = id_[(uint8_t)Byte::ID2Byte];
				buffer_[(uint8_t)Byte::ID3Byte] = id_[(uint8_t)Byte::ID3Byte];
				read_index_ = (uint8_t)Byte::ID3Byte;
			}
			else if ((uint32_t)read_index_ >= buffer_size_) {
				read_index_ = 0;
			}
		}
		return false;
	}

	/**
	 * Runs the currently loaded Cue.
	 */
	void CueController::run() {
		handlers_[buffer_[(uint8_t)Byte::PayloadByte]]->run(buffer_);
	}

	/**
	 * Validates and runs the specified Cue.
	 * @param cue Cue to load.
	 */
	void CueController::run(uint8_t *cue) {
		if (validate_header(cue)) {
			handlers_[cue[(uint8_t)Byte::PayloadByte]]->run(cue);
		}
	}

	/**
	 * Validates the header and checksum of the provided Cue.
	 * @param cue Cue to validate.
	 * @return True if valid, false if not.
	 */
	bool CueController::validate_header(uint8_t *cue) {
		// Check the ID
		for (uint8_t i = 0; i < (uint8_t)Byte::ChecksumByte; i++) {
			if (cue[i] != id_[i]) {
				return false;
			}
		}

		// Validate the Checksum
		uint16_t size = IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::SizeByte1]) + (uint8_t)Byte::PayloadByte;
		if (cue[(uint8_t)Byte::ChecksumByte] != checksum(cue, size)) {
			return false;
		}

		return true;
	}

	CueController::~CueController() {
		delete [] buffer_;
		for (uint8_t i = 0; i < 4; i++) {
			delete handlers_[i];
		}
	}
}

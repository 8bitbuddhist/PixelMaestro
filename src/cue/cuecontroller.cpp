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
	CueController::CueController(Maestro& maestro, uint32_t buffer_size) : maestro_(maestro) {
		this->buffer_size_ = buffer_size;
		this->buffer_ = new uint8_t[buffer_size] {0};
	}

	/**
	 * Prepares the Cue for transport by adding header info.
	 * @param payload_size The size of the payload.
	 * @return Assembled Cue.
	 */
	uint8_t* CueController::assemble(uint32_t payload_size) {
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

		buffer_[(uint8_t)Byte::ChecksumByte] = checksum(buffer_, payload_size);

		return buffer_;
	}

	/**
	 * Generates a checksum for verifying the integrity of a Cue.
	 * Calculated by summing each byte in the Cue, diving by 256, and taking the remainder.
	 * @param cue The contents of the Cue.
	 * @param cue_size The size of the Cue.
	 * @return New checksum.
	 */
	uint8_t CueController::checksum(const uint8_t* cue, uint32_t cue_size) {
		uint32_t sum = 0;
		for (uint32_t i = 0; i < cue_size; i++) {

			// Make sure we don't include the checksum in its own calculation
			if (i != (uint8_t)Byte::ChecksumByte) {
				sum += cue[i];
			}
		}

		return (sum % 256);
	}

	/**
	 * Enables the Animation CueHandler.
	 * @return New handler.
	 */
	CueHandler& CueController::enable_animation_cue_handler() {
		uint8_t handler	= (uint8_t)Handler::AnimationCueHandler;
		if (handlers_[handler] == nullptr) {
			handlers_[handler] = new AnimationCueHandler(*this);
		}
		return *handlers_[handler];
	}

	/**
	 * Enables the Canvas CueHandler.
	 * @return New handler.
	 */
	CueHandler& CueController::enable_canvas_cue_handler() {
		uint8_t handler	= (uint8_t)Handler::CanvasCueHandler;
		if (handlers_[handler] == nullptr) {
			handlers_[handler] = new CanvasCueHandler(*this);
		}
		return *handlers_[handler];
	}

	/**
	 * Enables the Maestro CueHandler.
	 * @return New handler.
	 */
	CueHandler& CueController::enable_maestro_cue_handler() {
		uint8_t handler	= (uint8_t)Handler::MaestroCueHandler;
		if (handlers_[handler] == nullptr) {
			handlers_[handler] = new MaestroCueHandler(*this);
		}
		return *handlers_[handler];
	}

	/**
	 * Enables the Section CueHandler.
	 * @return New handler.
	 */
	CueHandler& CueController::enable_section_cue_handler() {
		uint8_t handler	= (uint8_t)Handler::SectionCueHandler;
		if (handlers_[handler] == nullptr) {
			handlers_[handler] = new SectionCueHandler(*this);
		}
		return *handlers_[handler];
	}

	/**
	 * Enables the Show CueHandler.
	 * @return New handler.
	 */
	CueHandler& CueController::enable_show_cue_handler() {
		uint8_t handler	= (uint8_t)Handler::ShowCueHandler;
		if (handlers_[handler] == nullptr) {
			handlers_[handler] = new ShowCueHandler(*this);
		}
		return *handlers_[handler];
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
	uint32_t CueController::get_buffer_size() const {
		return buffer_size_;
	}

	/**
	 * Returns the size of the currently cached Cue.
	 * @return Cue size.
	 */
	uint32_t CueController::get_cue_size() const {
		return IntByteConvert::byte_to_uint32(&buffer_[(uint8_t)CueController::Byte::SizeByte1]);
	}

	/**
	 * Returns the size of the specified Cue.
	 * @param cue Cue to measure.
	 * @return Cue size.
	 */
	uint32_t CueController::get_cue_size(uint8_t *cue) const {
		return (IntByteConvert::byte_to_uint32(&cue[(uint8_t)CueController::Byte::SizeByte1]));
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
	Maestro& CueController::get_maestro() const {
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
		 *
		 * If we've reached the end of the payload, run the Cue then reset the read index.
		 * If we haven't reached the end, we want to check to see if this is an actual Cue being read.
		 * We do this by looking for the ID bytes, and if we see them, we clear the buffer and reset the read index so the Cue has room to load.
		 * We do the following checks:
		 *	1) Is the read index past the last ID byte? If so, move to the next check.
		 *	2) Is this a `ShowCueHandler::set_events()` Cue? If so, don't reset the buffer. Otherwise, we'd try to load each Event Cue as its own.
		 *	3) Do the last 3 bytes match the ID characters? If so, clear the buffer and reset the read index.
		 *
		 */
		uint32_t buffered_cue_size = IntByteConvert::byte_to_uint32(&buffer_[(uint8_t)Byte::SizeByte1]);
		if (buffered_cue_size > 0 && read_index_ >= buffered_cue_size) {
			run(buffer_);
			read_index_ = 0;
			return true;
		}
		else {
			if (read_index_ > (uint8_t)Byte::IDByte3 &&
					(buffer_[(uint8_t)Byte::PayloadByte] == (uint8_t)Handler::ShowCueHandler &&
						buffer_[(uint8_t)ShowCueHandler::Byte::ActionByte] != (uint8_t)ShowCueHandler::Action::SetEvents) &&
					(buffer_[read_index_ - (uint8_t)Byte::IDByte3] == id_[(uint8_t)Byte::IDByte1] &&
						buffer_[read_index_ - (uint8_t)Byte::IDByte2] == id_[(uint8_t)Byte::IDByte2] &&
						buffer_[read_index_] == id_[(uint8_t)Byte::IDByte3])) {

				buffer_[(uint8_t)Byte::IDByte1] = id_[(uint8_t)Byte::IDByte1];
				buffer_[(uint8_t)Byte::IDByte2] = id_[(uint8_t)Byte::IDByte2];
				buffer_[(uint8_t)Byte::IDByte3] = id_[(uint8_t)Byte::IDByte3];
				read_index_ = (uint8_t)Byte::IDByte3;
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
			if (handlers_[cue[(uint8_t)Byte::PayloadByte]] != nullptr) {
				handlers_[cue[(uint8_t)Byte::PayloadByte]]->run(cue);
			}
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
		uint32_t size = IntByteConvert::byte_to_uint32(&cue[(uint8_t)Byte::SizeByte1]);
		return (cue[(uint8_t)Byte::ChecksumByte] == checksum(cue, size));
	}

	CueController::~CueController() {
		delete [] buffer_;
		for (uint8_t i = 0; i < 5; i++) {
			delete handlers_[i];
		}
	}
}

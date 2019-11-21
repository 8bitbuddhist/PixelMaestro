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
		buffer_[(uint8_t)Byte::SizeByte3] = size.converted_2;
		buffer_[(uint8_t)Byte::SizeByte4] = size.converted_3;

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
	 * Checks whether the Cue is blocked according to the block list.
	 * @param cue Cue to check.
	 * @return True if blocked.
	 */
	bool CueController::is_blocked(const uint8_t *cue) const {
		for (uint8_t i = 0; i < num_blocked_cues_; i++) {
			BlockedCue& block = blocked_cues_[i];
			if ((cue[(uint8_t)Byte::PayloadByte] == (uint8_t)block.handler) &&
				(cue[(uint8_t)Byte::PayloadByte + 1] == block.action)) {
				return true;
			}
		}
		return false;
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
		 * Check to see if we should reset the read index in order to make room for the Cue.
		 */
		if (read_index_ > (uint8_t)Byte::IDByte3) {

			/*
			 * First, make sure this isn't a list of Show Events.
			 * If it is, the index will reset while reading an Event, which is a problem.
			 */
			if (!(buffer_[(uint8_t)Byte::PayloadByte] == (uint8_t)Handler::ShowCueHandler && buffer_[(uint8_t)ShowCueHandler::Byte::ActionByte] == (uint8_t)ShowCueHandler::Action::SetEvents)) {

				/*
				 * Next, move the read index to the start of the buffer and write the ID.
				 * Then, start reading after the last ID byte.
				 */
				if (buffer_[read_index_ - (uint8_t)Byte::IDByte3] == id_[(uint8_t)Byte::IDByte1] &&
					buffer_[read_index_ - (uint8_t)Byte::IDByte2] == id_[(uint8_t)Byte::IDByte2] &&
					buffer_[read_index_] == id_[(uint8_t)Byte::IDByte3]) {

					buffer_[(uint8_t)Byte::IDByte1] = id_[(uint8_t)Byte::IDByte1];
					buffer_[(uint8_t)Byte::IDByte2] = id_[(uint8_t)Byte::IDByte2];
					buffer_[(uint8_t)Byte::IDByte3] = id_[(uint8_t)Byte::IDByte3];
					read_index_ = (uint8_t)Byte::IDByte3 + 1;
					return false;
				}
			}
		}

		/*
		 * Check the size of the buffered Cue.
		 * If it's valid, we know how far to read the Cue.
		 * After reaching the end, run the Cue.
		 */
		if (read_index_ >= (uint8_t)Byte::SizeByte4) {
			uint32_t buffered_cue_size = IntByteConvert::byte_to_uint32(&buffer_[(uint8_t)Byte::SizeByte1]);
			if (buffered_cue_size > 0 && read_index_ >= buffered_cue_size) {
				run(buffer_);
				read_index_ = 0;
				return true;
			}
		}

		return false;
	}

	/**
	 * Runs the currently loaded Cue.
	 */
	void CueController::run() {
		if (handlers_[buffer_[(uint8_t)Byte::PayloadByte]] != nullptr && !is_blocked(buffer_)) {
			handlers_[buffer_[(uint8_t)Byte::PayloadByte]]->run(buffer_);
		}
	}

	/**
	 * Validates and runs the specified Cue.
	 * @param cue Cue to load.
	 */
	void CueController::run(uint8_t *cue) {
		if (handlers_[cue[(uint8_t)Byte::PayloadByte]] != nullptr && !is_blocked(cue) && validate_header(cue)) {
			handlers_[cue[(uint8_t)Byte::PayloadByte]]->run(cue);
		}
	}

	/**
	 * Sets the Cue block list.
	 * @param blocks Block list as an array of BlockedCues.
	 * @param num_blocks Number of items in the array.
	 */
	void CueController::set_blocked_cues(BlockedCue *blocks, uint8_t num_blocks) {
		this->blocked_cues_ = blocks;
		this->num_blocked_cues_ = num_blocks;
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

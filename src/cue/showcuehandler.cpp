#include "showcuehandler.h"

namespace PixelMaestro {

	uint8_t* ShowCueHandler::set_events(Event *events, uint16_t num_events, bool preserve_current_index) {
		IntByteConvert num_events_byte(num_events);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::ShowHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetEvents;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = num_events_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = num_events_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = (uint8_t)preserve_current_index;

		int options_index = (uint8_t)Byte::OptionsByte + 3;
		for (uint16_t event_index = 0; event_index < num_events; event_index++) {
			// Save time
			IntByteConvert event_time(events[event_index].get_time());
			controller_->get_buffer()[options_index] = event_time.converted_0;
			options_index++;
			controller_->get_buffer()[options_index] = event_time.converted_1;
			options_index++;

			// Save Cue
			uint8_t* event_cue = events[event_index].get_cue();
			for (uint16_t cue_index = 0; cue_index < controller_->get_cue_size(event_cue); cue_index++) {
				controller_->get_buffer()[options_index] = event_cue[cue_index];
				options_index++;
			}
		}

		return controller_->assemble(options_index);
	}

	uint8_t* ShowCueHandler::set_looping(bool loop) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::ShowHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetLooping;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)loop;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 1);
	}

	uint8_t* ShowCueHandler::set_timing_mode(Show::TimingMode timing) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::ShowHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetTimingMode;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)timing;

		return controller_->assemble((uint8_t)Byte::OptionsByte + 1);
	}

	void ShowCueHandler::run(uint8_t *cue) {
		Show* show = controller_->get_maestro()->get_show();

		if (show == nullptr) return;

		switch((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::SetEvents:
				{
					// Delete existing Events
					delete [] show->get_events();
					uint16_t num_events = IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]);
					bool preserve_cycle_index = cue[(uint8_t)Byte::OptionsByte + 2];

					// Rebuild Event list
					Event* events = new Event[num_events];
					int options_index = (uint8_t)Byte::OptionsByte + 3;
					for (uint16_t event = 0; event < num_events; event++) {
						// Set time
						uint32_t time = IntByteConvert::byte_to_int(&cue[options_index]);
						events[event].set_time(time);

						// Skip past the cue time to get the cue itself
						options_index += 2;

						// Set Cues
						uint16_t event_cue_size = controller_->get_cue_size(&cue[options_index]);
						events[event].set_cue(&cue[options_index]);
						options_index += event_cue_size;
					}

					show->set_events(events, num_events, preserve_cycle_index);
				}
				break;
			case Action::SetLooping:
				show->set_looping((bool)cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetTimingMode:
				show->set_timing_mode((Show::TimingMode)cue[(uint8_t)Byte::OptionsByte]);
				break;
		}
	}

	ShowCueHandler::~ShowCueHandler() { }
}

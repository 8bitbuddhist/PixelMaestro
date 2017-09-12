/*
	Show.cpp - Library for scheduling PixelMaestro animations.
*/

#include "show.h"

namespace PixelMaestro {

	/**
	 * Constructor.
	 * @param maestro The Maestro to control using this Show.
	 */
	Show::Show(Maestro* maestro) {
		maestro_ = maestro;
	}

	/**
		Returns whether the Show loops back over its Events, or if it just ends.

		@return Whether or not the Show loops.
	*/
	bool Show::get_looping() {
		return loop_;
	}

	/**
		Sets the Maestro that the Show will control.

		@param maestro Pointer to the Maestro that the show will control.
	*/
	void Show::set_maestro(Maestro* maestro) {
		maestro_ = maestro;
	}

	/**
		Sets the timing mode.

		@param timing Timing mode used.
	*/
	void Show::set_timing(TimingModes timing) {
		timing_ = timing;
	}

	/**
		Sets the Events in the Show.

		@param events Array of Events to queue.
		@param num_events The number of Events in the queue.
	*/
	void Show::set_events(Event** events, unsigned char num_events) {
		events_ = events;
		num_events_ = num_events;
	}

	/**
		Sets whether to loop when the Events are done running.

		@param loop If true, events will loop over from the beginning.
	*/
	void Show::set_looping(bool loop) {
		loop_ = loop;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Show::update(const unsigned long& current_time) {		
		// Only run if we're looping, or if we haven't reached the end of the Event list yet.
		if (loop_ || (!loop_ && current_index_ != num_events_)) {
			/*
				Based on the timing method used, determine whether to run the Event.
				If ABSOLUTE, compare the current time to the next Event's start time.
				If RELATIVE, compare the time since the last Event to the next Event's start time.
				After running the Event, update the last run time and current Event index.
			*/
			if ((timing_ == TimingModes::ABSOLUTE && (current_time >= events_[current_index_]->get_time())) ||
				(timing_ == TimingModes::RELATIVE && ((current_time - last_time_) >= events_[current_index_]->get_time()))) {
				events_[current_index_]->run();
				last_time_ = current_time;
				update_event_index();
			}
		}

		// Finally, update the Maestro
		maestro_->update(current_time);
	}

	// Private methods

	/**
		Updates the Event index.
	*/
	void Show::update_event_index() {
		// If we've exceeded the size of the array, start over from 0
		if (loop_ && (current_index_ + 1 >= num_events_)) {
			current_index_ = 0;
		}
		else {
			current_index_++;
		}
	}
}

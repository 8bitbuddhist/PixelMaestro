/*
	Show.cpp - Library for scheduling PixelMaestro animations.
*/

#include "show.h"

namespace PixelMaestro {

	Show::Show() {};

	/**
	 * Constructor.
	 * @param maestro The Maestro to control using this Show.
	 */
	Show::Show(Maestro *maestro) {
		maestro_ = maestro;
	}

	/**
		Returns the index of the currently queued Event.

		@return Index of the current Event.
	*/
	unsigned short Show::getCurrentIndex() {
		return current_index_;
	}

	/**
		Returns whether the Show loops back over its Events, or if it just ends.

		@return Whether or not the Show loops.
	*/
	bool Show::getLooping() {
		return loop_;
	}

	/**
		Returns the Maestro controlled by the Show.

		@return Maestro.
	*/
	Maestro *Show::getMaestro() {
		return maestro_;
	}

	/**
		Gets the index of the next Event.

		@return Index of the next Event.
	*/
	unsigned short Show::getNextIndex() {
		// Get the next index. If we've exceeded the size of the array, start over from 0
		if (current_index_ + 1 >= num_events_) {
			return 0;
		}
		else {
			return current_index_ + 1;
		}
	}

	/**
		Sets the Maestro that the Show will control.

		@param maestro Pointer to the Maestro that the show will control.
	*/
	void Show::setMaestro(Maestro *maestro) {
		maestro_ = maestro;
	}

	/**
		Sets the timing mode.

		@param timing Timing mode used.
	*/
	void Show::setTiming(TimingModes timing) {
		timing_ = timing;
	}

	/**
		Sets the Events in the Show.

		@param events Array of Events to queue.
		@param numEvents The number of Events in the queue.
	*/
	void Show::setEvents(Event** events, unsigned char numEvents) {
		events_ = events;
		num_events_ = numEvents;
	}

	/**
		Toggles whether to loop when the Events are done running.
	*/
	void Show::toggleLooping() {
		loop_ = !loop_;
	}

	/**
		Main update routine.

		@param currentTime Program runtime.
	*/
	void Show::update(const unsigned long &currentTime) {
		// Only run if we're looping, or if we haven't reached the end of the Event list yet.
		if (loop_ || (!loop_ && last_index_ != (num_events_ - 1))) {
			/*
				Based on the timing method used, determine whether to run the Event.
				If ABSOLUTE, compare the current time to the queued Event's start time.
				If RELATIVE, compare the time since the last Event to the queued Event's start time.
				After running the Event, update the last run time and last run Event index.
			*/
			if ((timing_ == TimingModes::ABSOLUTE && (currentTime >= events_[current_index_]->getTime())) ||
				(timing_ == TimingModes::RELATIVE && ((currentTime - last_time_) >= events_[current_index_]->getTime()))) {
				events_[current_index_]->run();
				last_index_ = current_index_;
				last_time_ = currentTime;
				current_index_ = getNextIndex();
			}
		}

		// Finally, update the Maestro
		maestro_->update(currentTime);
	}
}

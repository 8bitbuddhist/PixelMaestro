/*
	Show.cpp - Library for managing PixelMaestro transitions.
*/

#include "../include/Show.h"

namespace PixelMaestro {

	/**
		Returns the index of the currently queued Transition.

		@return Index of the current Transition.
	*/
	unsigned short Show::getCurrentIndex() {
		return current_index_;
	}

	/**
		Returns whether the Show loops back over its Transitions, or if it just ends.

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
		Gets the index of the next Transition.

		@return Index of the next Transition.
	*/
	unsigned short Show::getNextIndex() {
		// Get the next index. If we've exceeded the size of the array, start over from 0
		if (current_index_ + 1 >= num_transitions_) {
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
		Sets the Transitions in the Show.

		@param transitions Array of Transitions to queue.
		@param numTransitions The number of Transitions in the queue.
	*/
	void Show::setTransitions(Transition* transitions, unsigned char numTransitions) {
		transitions_ = transitions;
		num_transitions_ = numTransitions;
	}

	/**
		Toggles whether to loop when the Transitions are done running.
	*/
	void Show::toggleLooping() {
		loop_ = !loop_;
	}

	/**
		Main update routine.

		@param currentTime Program runtime.
	*/
	void Show::update(unsigned long currentTime) {
		// Only run if we're looping, or if we haven't reached the end of the Transition list yet.
		if (loop_ || (!loop_ && last_index_ != (num_transitions_ - 1))) {
			/*
				Based on the timing method used, determine whether to run the Transition.
				If ABSOLUTE, compare the current time to the queued Transition's start time.
				If RELATIVE, compare the time since the last Transition to the queued Transition's start time.
				After running the Transition, update the last run time and last run Transition index.
			*/
			if ((timing_ == TimingModes::ABSOLUTE && (currentTime >= transitions_[current_index_].time)) ||
				(timing_ == TimingModes::RELATIVE && ((currentTime - last_time_) >= transitions_[current_index_].time))) {
				transitions_[current_index_].action();
				last_index_ = current_index_;
				last_time_ = currentTime;
				current_index_ = getNextIndex();
			}
		}

		// Finally, update the Maestro
		maestro_->update(currentTime);
	}
}

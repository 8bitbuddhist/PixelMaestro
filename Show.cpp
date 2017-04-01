/*
	Show.cpp - Library for managing PixelMaestro transitions.
*/

#include "Show.h"

namespace PixelMaestro {

	/**
		Constructor.

		@param maestro The Maestro driving the show.
		@param transitions Array of Transitions to perform.
		@param numTransitions The number of Transitions in the array.
	*/
	Show::Show(Maestro *maestro, Transition *transitions, unsigned char numTransitions) {
		maestro_ = maestro;
		transitions_ = transitions;
		num_transitions_ = numTransitions;
	}

	/**
		Returns the index of the current Transition.

		@return Index of the current Transition.
	*/
	int Show::getCurrentIndex() {
		return current_index_;
	}

	/**
		Returns the current Transition.

		@return Current Transition.
	*/
	Show::Transition *Show::getCurrentTransition() {
		return &transitions_[current_index_];
	}

	/**
		Gets the index of the next Transition.

		@return Index of the next Transition.
	*/
	unsigned char Show::getNextIndex() {
		// Get the next index. If we've exceeded the size of the array, start over from 0
		if (current_index_ + 1 >= num_transitions_) {
			return 0;
		}
		else {
			return current_index_ + 1;
		}
	}

	/**
		Main update routine.

		@param currentTime Program runtime.
	*/
	void Show::update(unsigned long currentTime) {
		// If the program time is past the Transition's scheduled time and the Transition has not already ran, run it.
		if (currentTime >= transitions_[current_index_].time && !transitions_[current_index_].ran) {
			runTransition(&transitions_[current_index_]);
		}
		maestro_->update(currentTime);
	}

	/**
		Runs a Transition on the Maestro.

		@param transition Transition to run.
	*/
	void Show::runTransition(Transition *transition) {
		Opts opts = transition->opts;

		// Determine how to proceed based on the Transition action.
		switch (transition->action) {
			case Actions::SET_UPDATE_SPEED:
				// Change the update speed of a Section to val1.
				maestro_->getSection(opts.sectionNum)->setUpdateSpeed(transition->opts.val1);
				break;
			case Actions::SET_COLOR_ANIMATION:
				// Change the color animation of a Section.
				maestro_->getSection(opts.sectionNum)->setColorAnimation(opts.animation, opts.val1);
				break;
			case Actions::TOGGLE_FADE:
				// Toggle fading on a Section.
				maestro_->getSection(opts.sectionNum)->toggleFade();
				break;
			default:
				break;
		}

		// Mark the Transition as having executed.
		transition->ran = true;
		current_index_ = getNextIndex();
	}

	Show::~Show() {}
}

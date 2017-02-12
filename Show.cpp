/*
	Show.cpp - Library for managing PixelMaestro transitions.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
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
				// Change the update speed of a Grid or Line to val1.
				if (opts.line && opts.grid) {
					maestro_->getGrid(opts.gridNum)->getLine(opts.lineNum)->setUpdateSpeed(transition->opts.val1);
				}
				else if (opts.grid) {
					maestro_->getGrid(opts.gridNum)->setUpdateSpeed(transition->opts.val1);
				}
				else if (opts.line) {
					maestro_->getLine(opts.lineNum)->setUpdateSpeed(transition->opts.val1);
				}
				break;
			case Actions::SET_COLOR_ANIMATION:
				// Change the color animation of a Grid or Line to gridAnimation or lineAnimation.
				if (opts.line && opts.grid) {
					maestro_->getGrid(opts.gridNum)->getLine(opts.lineNum)->setColorAnimation(opts.lineAnimation, opts.val1);
				}
				else if (opts.grid) {
					maestro_->getGrid(opts.gridNum)->setColorAnimation(opts.gridAnimation, opts.val1);
				}
				else if (opts.line) {
					maestro_->getLine(opts.lineNum)->setColorAnimation(opts.lineAnimation, opts.val1);
				}
				break;
			case Actions::TOGGLE_FADE:
				// Toggle fading on a Grid or Line.
				if (opts.line && opts.grid) {
					maestro_->getGrid(opts.gridNum)->getLine(opts.lineNum)->toggleFade();
				}
				else if (opts.grid) {
					maestro_->getGrid(opts.gridNum)->toggleFade();
				}
				else if (opts.line) {
					maestro_->getLine(opts.lineNum)->toggleFade();
				}
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
